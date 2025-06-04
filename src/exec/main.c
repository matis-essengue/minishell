/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: armosnie <armosnie@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/26 16:27:00 by armosnie          #+#    #+#             */
/*   Updated: 2025/06/04 16:11:13 by armosnie         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"

bool    is_here_doc(t_data *data, char *arg)
{
    if (ft_strncmp("here_doc", arg, 9) == 0)
    {
        data->here_doc = true;
        return (true);
    }
    else
    {
        data->here_doc = false;
    }
    return (false);  
}
bool	init_data_with_here_doc(t_data *data, int argc, char *argv[], char **envp)
{
    data->outfile = argv[argc - 1];
    data->infile = NULL;
    data->limiter = argv[2];
    data->n_cmd = argc - 4;
    data->cmd = argv + 3;
    data->cmd[argc - 4] = NULL;
    data->envp = envp;
    return (true);
}
bool	init_data(t_data *data, int argc, char *argv[], char **envp)
{
    data->outfile = argv[argc - 1];
    data->infile = argv[1];
    data->limiter = NULL;
    data->n_cmd = argc - 3;
    data->cmd = argv + 2;
    data->cmd[argc - 3] = NULL;
    data->envp = envp;
	return (true);
}

int	main(int argc, char *argv[], char **envp)
{
	t_data data;

    if (argc < 5)
        f_error("not enough arg\n", 1);
    if (is_here_doc(&data, argv[1]) == true)
    {
        if (argc < 6)
            f_error("not enough arg with here_doc\n", 1);
		if (init_data_with_here_doc(&data, argc, argv, envp) == false)
			f_error("init failed\n", 1);
        manage_here_doc(&data);
		pipe_function(&data);
	}
    else
    {
        if (init_data(&data, argc, argv, envp) == false)
            f_error("init failed\n", 1);
		pipe_function(&data);
    }
	return (0);
}
