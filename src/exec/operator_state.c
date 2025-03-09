/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operator_state.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cbopp <cbopp@student.42lausanne.ch>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 17:12:52 by cbopp             #+#    #+#             */
/*   Updated: 2025/03/04 19:33:10 by cbopp            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

/**
 * @brief Save the current state before executing sublist
 * @param mini shell state
 * @param state struct to save state in
 */
void	save_exec_state(t_mini *mini, t_state *state)
{
	state->original_token = mini->token;
	state->original_is_pipe = mini->is_pipe;
	state->original_pipe_num = mini->pipe_num;
}

/**
 * @brief Restore the shell state after executiong
 * @param mini shell state
 * @param state saved state
 */
void	restore_exec_state(t_mini *mini, t_state *state)
{
	mini->token = state->original_token;
	mini->is_pipe = state->original_is_pipe;
	mini->pipe_num = state->original_pipe_num;
}
