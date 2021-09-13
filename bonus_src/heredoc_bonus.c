/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmai <fmai@student.42tokyo.jp>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/07 17:43:32 by fmai              #+#    #+#             */
/*   Updated: 2021/09/13 17:09:12 by fmai             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./pipex_bonus.h"

int	stdin_from_heredoc(int doc_pipe[2], char *limiter)
{
	int		pid;
	char	*line;
	int		ret;

	pid = fork();
	if (pid == 0)
	{
		handle_close(doc_pipe[0]);
		while (true)
		{
			ret = get_next_line(0, &line);
			if (ft_strcmp(line, limiter))
			{
				free(line);
				break ;
			}
			write(doc_pipe[1], line, ft_strlen(line));
			write(doc_pipe[1], "\n", 1);
			free(line);
		}
		handle_close(doc_pipe[1]);
		exit(0);
	}
	return (pid);
}

int	exec_first_command_with_heredoc(
	int pipe_a[2], char *raw_command, char **envp, char *limiter)
{
	int		pid;
	int		heredoc_pid;
	int		doc_pipe[2];

	pipe(doc_pipe);
	pid = fork();
	if (pid == -1)
		exit_with_perr("fork()", NULL, NULL);
	if (pid == 0)
	{
		handle_close(doc_pipe[1]);
		if (dup2(doc_pipe[0], 0) == -1)
			exit_with_perr("dup2()", NULL, NULL);
		handle_close(doc_pipe[0]);
		if (dup2(pipe_a[1], 1) == -1)
			exit_with_perr("dup2()", NULL, NULL);
		handle_close(pipe_a[1]);
		handle_close(pipe_a[0]);
		handle_command(raw_command, envp);
	}
	heredoc_pid = stdin_from_heredoc(doc_pipe, limiter);
	handle_close(doc_pipe[0]);
	handle_close(doc_pipe[1]);
	waitpid(heredoc_pid, NULL, 0);
	return (pid);
}
