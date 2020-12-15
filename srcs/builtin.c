#include "./../includes/minishell.h"

int	ft_cd(char *path)
{
	if (chdir(path) == -1)
		return (1); //implementer error
	return (0);
}

int ft_pwd(void)
{
	char *current_dir;

	current_dir = NULL;

	if ((current_dir = getcwd(current_dir, 0)) == NULL)
		return (1); //implementer error
//	printf("%s\n", current_dir);
//	changer la variable d'environnement.	
	ft_putstr_fd(current_dir, 1);
	ft_putchar_fd('\n', 1);
	free(current_dir);
	return (0);
}