/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_heredoc_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 18:36:48 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/21 18:43:11 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Finds next command in pipeline after a pipe
 * @param current Current token
 * @return Next command token after pipe
 */
static t_token	*find_next_cmd_after_pipe(t_token *current)
{
	t_token	*next_pipe;

	next_pipe = find_next_pipe_token(current);
	if (next_pipe && next_pipe->next)
		return (next_pipe->next);
	return (NULL);
}

/**
 * @brief Execute command at current position in pipeline
 * @param mini Shell state
 * @param p Pipe information structure
 * @param i Command index
 * @return 0 on success, 1 on failure
 */
static int	execute_cmd_in_pipe(t_mini *mini, t_pipe *p, int i)
{
	p->pids[i] = exec_pipe_cmd_heredoc(mini, i, p->pipe_fds);
	if (p->pids[i] == -1)
	{
		free(p->pipe_fds);
		free(p->pids);
		return (1);
	}
	return (0);
}

/**
 * @brief Processes all commands in the pipeline
 * @param mini Shell state
 * @param p Pipe information
 * @param start_token First token in pipeline
 * @return 0 on success, 1 on failure
 */
static int	process_pipeline_cmds(t_mini *mini, t_pipe *p, t_token *start_token)
{
	int		i;
	t_token	*current;

	i = 0;
	current = start_token;
	while (i <= mini->pipe_num)
	{
		mini->token = current;
		if (execute_cmd_in_pipe(mini, p, i))
			return (1);
		if (i < mini->pipe_num)
		{
			current = find_next_cmd_after_pipe(current);
			if (!current)
				break;
		}
		i++;
	}
	return (0);
}

/**
 * @brief Updates a pipeline of commands to use preprocessed heredocs
 * @param mini Shell state
 * @param p Pipe information structure
 * @return 0 on succcess, 1 on failure
 */
int	run_pipe_commands_heredoc(t_mini *mini, t_pipe *p)
{
	t_token	*start_token;
	int		result;

	start_token = mini->token;
	result = process_pipeline_cmds(mini, p, start_token);
	mini->token = start_token;
	return (result);
}
