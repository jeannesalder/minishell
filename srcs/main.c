#include "./../includes/minishell.h"

char	*ft_cat(char *input, char c)
{
	int i;
	char *str;

	i = 0;
	while (input[i])
		i++;
	if (!(str = malloc((i + 2) * sizeof(char))))
		return (NULL);
	i = 0;
	while(input[i])
	{
		str[i] = input[i];
		i++;
	}
	str[i] = c;
	str[i + 1] = 0;
	free(input);
	return(str);
}

char	*ft_read_input()
{
	int ret;
	char c;
	char *input = NULL;
	
	write (1, "> ", 2);

		if (!(input = malloc(sizeof(char) * 1)))
			return(NULL);
		input[0] = 0; 
		ret = read(0, &c, 1);
		if (ret == 0)
		{
			write(1, "\n", 1);
			exit(0);
		}
		while (c != '\n')
		{
			input = ft_cat(input, c);
			ret = read(0, &c, 1);
		}
		if (ret == -1 || input == NULL)
			return(NULL);
		return(input);
}

char	*get_path(char **envp)
{
	char* path = NULL;
	int i;

	i = 0;
	while (envp[i] != NULL && path == NULL)
	{
		if (strncmp(envp[i], "PATH=", 5) == 0)
			path = ft_substr(envp[i], 5, ft_strlen(envp[i]) - 5);
		i++;
	}
	return(path);
}

char *get_cmd_path(char *path, char *cmd)
{
	char **path_split = NULL;
	struct stat	file;

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

int	ft_exec_cmd(char **envp, char *path, char *cmd)
{

	char* arg[] = {cmd, "toto", NULL};
	pid_t child_pid;
	int wstatus;

	//si cmd n'est pas deja un chemin
	path = get_cmd_path(path, cmd);
	child_pid = fork();
	if (child_pid < 0)
		return(-1);
	else if (child_pid == 0)
	{
		signal(SIGINT, SIG_DFL); //necessaire ?
		if (execve(path, arg, envp) == -1)
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

void sigint_handler(int signo)
{
	(void)signo;
	write(1, "En construction...", 18);
	//reset shell : free input et ft_read ? 
}

int	main(int ac, char **av, char **envp)
{

	(void)ac;
	(void)av;
	
	char *input;

	char *path = get_path(envp);
	signal(SIGINT, sigint_handler);
	while (1)
	{
		input = ft_read_input();
		if (ft_strncmp("cd", input, 2) == 0)
		{
			if (ft_cd("/tmp/") == 1)
				return(1);
		}
		if (ft_strncmp("pwd", input, 3) == 0)
		{
			if (ft_pwd() == 1)
				return(1);
		}
		if (ft_strncmp("mkdir", input, 4) == 0)
		{
			char *cmd = "mkdir";  //en attendant le parsing;
			ft_exec_cmd(envp, path, cmd);
		}
		free(input);
	}	
}
