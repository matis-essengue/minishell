typedef enum input_type
{
    STDIN,
    PIPEIN,
    HERE_DOC,
    INFILE,
} t_input_type;

typedef enum output_type
{
    STDOUT,
    PIPEOUT,
    OUTFILE,
	OUTFILE_APPEND,
} t_output_type;

typedef struct s_heredoc
{
	char				*delimiter;
	char				*content;
	int					expand_vars;
	struct s_heredoc	*next;
} t_heredoc;

typedef struct s_cmd
{
    char    *name;
    char    **args;
	char	*infile;
	char	*outfile;
    t_input_type input_type;
    t_output_type output_type;
	t_heredoc *heredocs;
	struct s_cmd	*next;
} t_cmd;
