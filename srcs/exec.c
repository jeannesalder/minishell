#include "./../includes/minishell.h"

char *get_cmd_path(char *path, char *cmd)
{
	char *tmp;
	char *cmd_path;
	char **path_split;
	struct stat	file;

	path_split = NULL;

//verifier la s'íl sagit deja d´un chemin (commence par / ou ./).
//Cas ou path est nul
	path_split = ft_split(path, ':');

	int i = 0;

	while(path_split[i] != NULL)
	{
		tmp = ft_strjoin(path_split[i], "/");
		cmd_path = ft_strjoin(tmp, cmd);
		free(tmp);
		if (stat(cmd_path, &file) == 0)
		{
			free_strarray(path_split);
			return(cmd_path);
		}
		//a completer;
		i++;
		free(cmd_path);
	}
	free_strarray(path_split);
	return (NULL);
}

int ft_execve(t_var *shell)
{
//	char* arg[] = {shell->cmd[0], "toto", NULL};
	char *path;
	pid_t child_pid;
	int wstatus;

	if ((path = get_cmd_path(shell->path, shell->cmd[0])))
	{
		child_pid = fork();
		if (child_pid < 0)
			return(-1);
		else if (child_pid == 0)
		{
			signal(SIGINT, SIG_DFL); //necessaire ?
			if (execve(path, shell->cmd, shell->env) == -1)
				return(-1); 
			//-> besoin de parser le chemin absolu, il present dans la variable d'en PATH mais besoin de tester tous les chemins. stat(path, &file) ?	
		}
		else
		{
			waitpid(child_pid, &wstatus, 0);
			kill(child_pid, SIGTERM); 
			//a quoi ca sert de tuer le process ?
		}
		free(path);
    	return (1);
    }
    // ft_printf("bash: %s: command not found\n", shell->cmd[0]);
    ft_putstr_fd("bash: %s: command not found\n", 1); //remplacer par printf quand j'aurais reussi a changer le Makefile
    return (0);
}

int is_a_built(t_var *shell, char *cmd)
{
	if (ft_memcmp(cmd, "echo", 5) == 0)
		ft_echo(shell, shell->cmd);
	else if (ft_memcmp(cmd, "cd", 3) == 0)
		ft_cd(shell, shell->cmd);
	else if (ft_memcmp(cmd, "pwd", 4) == 0)
		ft_pwd(shell);
	// else if (ft_memcmp(cmd, "export", 7) == 0)
		// ft_export(shell);
	// else if (ft_memcmp(cmd, "unset", 5) == 0)
		// ft_unset(shell);
	// else if (ft_memcmp(cmd, "env", 4) == 0)
		// ft_env(shell);
	// else if (ft_memcmp(cmd, "exit", 5) == 0)
		// ft_exit(shell);
	else
		return (0);
	return (1);
}

int	ft_exec_cmd(t_var *shell)
{
	if (!(is_a_built(shell, shell->cmd[0])))
		ft_execve(shell);
	return (1); // ret a changer;
}