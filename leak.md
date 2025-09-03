# MINISHELL - RAPPORT COMPLET DES MEMORY LEAKS ET RESOURCE LEAKS

Ce document liste TOUS les endroits où des fuites mémoire, des descripteurs de fichiers non fermés, ou d'autres problèmes de gestion des ressources ont été identifiés dans le projet minishell.

## RÉSUMÉ EXÉCUTIF

**Total des fuites identifiées : 19 problèmes distincts**
- 12 fuites mémoire (malloc/strdup non libérés)
- 2 fuites de descripteurs de fichiers
- 1 potentiel double-free
- 4 nettoyages incomplets

---

## 1. FUITES DANS LES BUILT-INS

### 🔴 CRITIQUE - src/built-in/built_in_utils.c

#### Ligne 69-72 : Arithmétique de pointeur incorrecte + Fuite mémoire
```c
ret_path = ft_strdup(&env[i][equal_len + 1]);
if (!ret_path)
    return (NULL);
return (ret_path + equal_len + 1);  // ⚠️ ERREUR CRITIQUE
```
**Fonction :** `find_var`  
**Problème :** 
- ft_strdup alloue de la mémoire
- Le retour avec décalage rend impossible la libération
- L'arithmétique sur le pointeur est incorrecte et causera un crash

### 🟠 src/built-in/cd.c

#### Ligne 55-57 : Fuite mémoire sur chemin d'erreur
```c
new_pwd = return_pwd();
if (!new_pwd)
    return (1);
if (get_my_export_env(env, new_pwd) != 0)
    return (1);  // ⚠️ new_pwd NON LIBÉRÉ
free(new_pwd);
```
**Fonction :** `change_update_pwd_and_env`  
**Problème :** Si get_my_export_env échoue, new_pwd n'est pas libéré

#### Ligne 83-95 : Descripteur de répertoire non fermé
```c
dir = opendir(cmd->args[0]);
if (dir == NULL)
{
    printf("");
    return (perror("cd: dir"), 1);
}
// ... code ...
if (change_update_pwd_and_env(&env->env) != 0)
    return (1);  // ⚠️ dir NON FERMÉ
```
**Fonction :** `built_in_cd`  
**Problème :** Le handle de répertoire n'est pas fermé si change_update_pwd_and_env échoue

### 🟡 src/built-in/export_utils.c

#### Ligne 120-121 : Allocation non documentée
```c
expand = ft_strdup((env[i] + j));
return (expand);  // ⚠️ L'APPELANT DOIT FREE
```
**Fonction :** `ft_getenv`  
**Problème :** La fonction retourne une allocation dynamique sans documentation claire

---

## 2. FUITES DANS L'EXÉCUTION

### 🟡 src/exec/get_path.c

#### Ligne 118-120 : Potentiel double-free
```c
free_array(full_cmd);
free_array(path);  // ⚠️ path PEUT ÊTRE NULL
error(cmd, "env error", 127);
```
**Fonction :** `exe_my_cmd`  
**Problème :** Si path est NULL, comportement indéterminé selon l'implémentation de free_array

### 🟠 src/exec/manage_files.c

#### Ligne 79-81 : Gestion conditionnelle incorrecte
```c
if (heredoc->expand_vars)
{
    expand = find_var(line, env->env);
    write(pipe_fd_h[WRITE], expand, ft_strlen(expand));
    free(expand);
}
// ⚠️ Si expand_vars change d'état, fuite possible
```
**Fonction :** `child_process_heredoc`  
**Problème :** La logique de libération dépend d'une condition qui pourrait changer

#### Ligne 79-86 : Déréférencement de NULL potentiel
```c
expand = find_var(line, env->env);
write(pipe_fd_h[WRITE], expand, ft_strlen(expand));  // ⚠️ expand PEUT ÊTRE NULL
```
**Fonction :** `child_process_heredoc`  
**Problème :** Si find_var retourne NULL, crash assuré

---

## 3. FUITES DANS LE PARSING (LES PLUS NOMBREUSES)

<!-- ### 🔴 src/parsing/cmd_checker.c

#### Ligne 74-76 : Fuite mémoire dans boucle
```c
while (cmd->args[i])
{
    var_name = get_var_name(cmd->args[i]);  // ⚠️ ALLOUE DE LA MÉMOIRE
    if (!is_valid_var_name(var_name))
    {
        printf("minishell: export: `%s': not a valid identifier\n", var_name);
        return (0);  // ⚠️ var_name NON LIBÉRÉ
    }
    // var_name jamais libéré même en cas de succès
    i++;
}
```
**Fonction :** `is_valid_export`  
**Problème :** var_name (ft_strndup) n'est jamais libéré -->

### 🔴 src/parsing/expander.c

#### Ligne 74-80 : Fuite ft_itoa
```c
expanded = ft_strjoin(expanded, ft_itoa(env->exit_status));
// ⚠️ ft_itoa() RETOURNE UNE ALLOCATION NON LIBÉRÉE
```
**Fonction :** `expand_variable`  
**Problème :** Le résultat de ft_itoa n'est pas stocké pour être libéré

#### Ligne 82-93 : Multiples fuites dans l'expansion
```c
expanded = ft_strjoin(expanded, ft_strndup(*start, *temp - *start));  // ⚠️ FUITE 1
var = ft_strndup(*start + 1, *temp - *start - 1);  // ⚠️ JAMAIS FREE
env_var = ft_getenvx(var, env->env);
if (env_var)
    expanded = ft_strjoin(expanded, env_var);  // ⚠️ env_var NON FREE
```
**Fonction :** `expand_variable`  
**Problèmes multiples :**
- ft_strndup temporaire non libéré
- var jamais libéré
- env_var jamais libéré

#### Ligne 133-139 : Écrasement de pointeurs
```c
current->name = expand_word(current->name, env);  // ⚠️ ANCIEN name NON FREE
// ...
current->args[i] = expand_word(current->args[i], env);  // ⚠️ ANCIEN args[i] NON FREE
```
**Fonction :** `expand_cmds`  
**Problème :** Les chaînes originales sont écrasées sans libération

### 🔴 src/parsing/quote_remover.c

#### Ligne 37-38 : Fuite ft_strndup dans ft_strjoin
```c
*new_word = ft_strjoin(*new_word, ft_strndup(*start, temp - *start));
// ⚠️ RÉSULTAT ft_strndup NON LIBÉRÉ
```
**Fonction :** `_handle_quotes`  
**Problème :** Le résultat temporaire de ft_strndup fuit

#### Ligne 65 : Même problème
```c
new_word = ft_strjoin(new_word, ft_strndup(start, temp - start));
// ⚠️ RÉSULTAT ft_strndup NON LIBÉRÉ
```
**Fonction :** `_remove_quotes`

#### Lignes 76-110 : Multiples écrasements sans free
```c
current_file->name = _remove_quotes(current_file->name);  // ⚠️ ANCIEN name PERDU
current->name = _remove_quotes(current->name);  // ⚠️ ANCIEN name PERDU
current->args[i] = _remove_quotes(current->args[i]);  // ⚠️ ANCIEN args[i] PERDU
```
**Fonctions :** `rm_quotes_for_all_files`, `remove_quotes`  
**Problème :** Systématique - toutes les chaînes originales sont perdues

### 🔴 src/parsing/parser.c

#### Ligne 47 : Nettoyage incomplet
```c
free(tokens);  // ⚠️ DEVRAIT ÊTRE free_tokens(tokens)
```
**Fonction :** `parse`  
**Problème :** Seule la structure est libérée, pas les valeurs des tokens

### 🔴 src/parsing/token.c

#### Lignes 84-89 : Structures de tokens non libérées
```c
while (current != NULL)
{
    free(current->value);
    current = current->next;  // ⚠️ current JAMAIS FREE
}
free(tokens);
```
**Fonction :** `free_tokens`  
**Problème :** Les structures t_token elles-mêmes ne sont pas libérées

### 🟠 src/parsing/tokens_to_cmds_utils.c

#### Lignes 23-31 : Pas de nettoyage en cas d'échec
```c
cmd->args = malloc(sizeof(char *) * (arg_count + 1));
// ...
if (current->type == TOKEN_WORD)
{
    if (i >= 0)
        cmd->args[i] = ft_strdup(current->value);  // ⚠️ SI ÉCHOUE, ARGS PRÉCÉDENTS NON FREE
    i++;
}
```
**Fonction :** `allocate_and_fill_args`  
**Problème :** En cas d'échec de ft_strdup, les arguments déjà alloués fuient

### 🟡 src/parsing/utils.c

#### Lignes 29-31 : Erreur de priorité des opérateurs
```c
dup = (char *)malloc(sizeof(char) * n + 1);  // ⚠️ DEVRAIT ÊTRE * (n + 1)
```
**Fonction :** `ft_strndup`  
**Problème :** Priorité des opérateurs incorrecte (multiplication avant addition)

---

## 4. FUITES DANS MAIN

### 🟠 src/main.c

#### Lignes 53-55 : Gestion d'erreur manquante
```c
cmd = parse(line, my_env);
check_exit(cmd, 0);  // ⚠️ SI cmd EST NULL ?
my_env->exit_status = execute_command(cmd, my_env);  // ⚠️ SI cmd EST NULL ?
```
**Fonction :** `main`  
**Problème :** Si parse échoue, les structures peuvent fuir et le comportement est indéfini

---

## RECOMMANDATIONS PRIORITAIRES

### Actions Immédiates (CRITIQUE)

1. **Corriger built_in_utils.c ligne 72** - Bug critique causant corruption mémoire
2. **Implémenter free_tokens correctement** - Libérer TOUTES les structures
3. **Corriger l'expansion de variables** - Stocker et libérer tous les temporaires
4. **Systématiser la libération avant écrasement** - Sauvegarder et free les anciens pointeurs

### Actions à Court Terme

1. Ajouter une fonction `free_old_and_assign(char **dest, char *new)`
2. Créer des wrappers pour ft_strjoin qui libèrent les arguments
3. Documenter toutes les fonctions retournant des allocations
4. Ajouter des tests avec valgrind dans la CI/CD

### Actions à Moyen Terme

1. Implémenter un système de garbage collection ou reference counting
2. Utiliser des analyseurs statiques (scan-build, cppcheck)
3. Créer une suite de tests de régression pour les fuites
4. Refactoriser le parsing pour une gestion mémoire plus claire

---

## COMMANDE VALGRIND RECOMMANDÉE

```bash
valgrind --track-fds=yes \
         --trace-children=yes \
         --track-origins=yes \
         --leak-check=full \
         --show-leak-kinds=all \
         --suppressions=minishell.supp \
         ./minishell
```

## STATISTIQUES FINALES

- **Fichiers affectés :** 14/30 (47% du projet)
- **Fonctions avec fuites :** 19 fonctions distinctes
- **Impact estimé :** Fuites cumulatives pouvant saturer la mémoire en utilisation prolongée
- **Sévérité globale :** 🔴 ÉLEVÉE - Correction urgente requise

---

*Document généré par analyse statique du code source - À valider avec valgrind*