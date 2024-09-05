/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:45:08 by jmakkone          #+#    #+#             */
/*   Updated: 2024/08/30 01:35:06 by jmakkone         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_outside_state(t_parse_state *state, char **cmd)
{
	if (**cmd == ' ')
	{
		if (state->arg)
		{
			state->args = add_arg(state->args, state->arg, \
					&state->argc, &state->arg_size);
			state->arg = NULL;
		}
	}
	else if (**cmd == '\\')
		state->state = ESCAPE_SEQUENCE;
	else if (**cmd == '\'')
		state->state = INSIDE_SINGLE_QUOTE;
	else if (**cmd == '\"')
		state->state = INSIDE_DOUBLE_QUOTE;
	else
		state->arg = append_char(state->arg, **cmd);
}

static void	handle_inside_single_quote_state(t_parse_state *state, char **cmd)
{
	if (**cmd == '\'')
		state->state = OUTSIDE;
	else
		state->arg = append_char(state->arg, **cmd);
}

static void	handle_inside_double_quote_state(t_parse_state *state, char **cmd)
{
	if (**cmd == '\"')
		state->state = OUTSIDE;
	else if (**cmd == '\\' && (*(*cmd + 1) == '\"' || *(*cmd + 1) == '\\'))
	{
		(*cmd)++;
		state->arg = append_char(state->arg, **cmd);
	}
	else
		state->arg = append_char(state->arg, **cmd);
}

static void	parse_argument_loop(t_parse_state *state, char **cmd)
{
	while (**cmd)
	{
		if (state->state == ESCAPE_SEQUENCE)
		{
			state->arg = append_char(state->arg, **cmd);
			state->state = OUTSIDE;
		}
		else if (state->state == OUTSIDE)
			handle_outside_state(state, cmd);
		else if (state->state == INSIDE_SINGLE_QUOTE)
			handle_inside_single_quote_state(state, cmd);
		else if (state->state == INSIDE_DOUBLE_QUOTE)
			handle_inside_double_quote_state(state, cmd);
		(*cmd)++;
	}
}

char	**parse_arguments(char *cmd)
{
	t_parse_state	state;

	state.args = malloc(ARG_ARR_SIZE * sizeof(char *));
	if (!state.args)
		return (NULL);
	state.arg = NULL;
	state.argc = 0;
	state.arg_size = ARG_ARR_SIZE;
	state.state = OUTSIDE;
	parse_argument_loop(&state, &cmd);
	if (state.arg)
		state.args = add_arg(state.args, state.arg, \
				&state.argc, &state.arg_size);
	state.args[state.argc] = NULL;
	return (state.args);
}
