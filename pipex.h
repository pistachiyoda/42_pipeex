#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "./libft/libft.h"
int	first_exec(int pipe_fds[2], char **argv, char **envp);
int	last_exec(int pipe_fds[2], char **argv, char **envp);
void	free_2d_array(char **two_d_array);
void	error(char *message, char **free_string_array, char *free_string);
int	check_readability(char *file);
int	check_writability(char *file);
int		open_file(char *file);
int		open_or_create_file(char *file);
int		is_executable(char *command);
char	*get_env(char *key, char **envp);
char	**split_command(char *unformatted_command);
char	*resolve_path(char *command, char *path_env);
void	handle_command(char *raw_command, char **envp);
void	error_str(char *message, char **free_string_array, char *free_string);
//
#include <stdio.h>