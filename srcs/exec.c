#include "./../includes/minishell.h"

char *get_cmd_path(char *path, char *cmd)
{
	char **path_split = NULL;
	struct stat	file;

//verifier la s'íl sagit deja d´un chemin (commence par / ou ./).
//Cas ou path est nul
	path_split = ft_split(path, ':');

	int i = 0;

	while(path_split[i] != NULL)
	{
		path = ft_strjoin(path_split[i], "/");
		path = ft_strjoin(path, cmd);
		if (stat(path,	 &file) == 0)
			return(path);
		//a completer;
		i++;
	}

	return (NULL);
}

int	ft_exec_cmd(t_var *shell)
{

	char* arg[] = {shell->cmd[0], "toto", NULL};
	char *path;
	pid_t child_pid;
	int wstatus;

	//si cmd n'est pas deja un chemin
	path = get_cmd_path(shell->path, shell->cmd[0]);
	child_pid = fork();
	if (child_pid < 0)
		return(-1);
	else if (child_pid == 0)
	{
		signal(SIGINT, SIG_DFL); //necessaire ?
		if (execve(path, arg, shell->env) == -1)
			return(-1); 
		//-> besoin de parser le chemin absolu, il present dans la variable d'en PATH mais besoin de tester tous les chemins. stat(path, &file) ?	
	}
	else
	{
		waitpid(child_pid, &wstatus, 0);
		kill(child_pid, SIGTERM); 
		//a quoi ca sert de tuer le process ?
	}
    return(1);
}