/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_argument.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:45:08 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/25 14:54:43 by mpellegr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	handle_outside_state(t_parse_state *state, char *cmd, int i)
{
	if (cmd[i] == ' ' || cmd[i] == '\t')
	{
		if (state->arg)
		{
			state->args = add_arg(state->args, state->arg, \
					&state->argc, &state->arg_size);
			state->arg = NULL;
		}
	}
	else if (cmd[i] == '\\')
		state->state = ESCAPE_SEQUENCE;
	else if (cmd[i] == '\'')
		state->state = INSIDE_SINGLE_QUOTE;
	else if (cmd[i] == '\"')
		state->state = INSIDE_DOUBLE_QUOTE;
	else
		state->arg = append_char(state->arg, cmd[i]);
}

static void	handle_in_single_quote(t_parse_state *state, char c)
{
	if (c == '\'')
		state->state = OUTSIDE;
	else
	{
		if (c == '$')
			state->dollar_sign = 1;
		state->arg = append_char(state->arg, c);
	}
}

static void	handle_in_double_quote(t_parse_state *state, char *cmd, int *i)
{
	if (cmd[*i] == '\"')
		state->state = OUTSIDE;
	else if (cmd[*i] == '\\' && (cmd[*i + 1] == '\"' || cmd[*i + 1] == '\\'))
	{
		(*i)++;
		state->arg = append_char(state->arg, cmd[*i]);
	}
	else
		state->arg = append_char(state->arg, cmd[*i]);
}

static void	parse_argument_loop(t_parse_state *state, char *cmd)
{
	int	i;

	i = 0;
	while (cmd[i])
	{
		if (state->state == ESCAPE_SEQUENCE)
		{
			state->arg = append_char(state->arg, cmd[i]);
			state->state = OUTSIDE;
		}
		else if (state->state == OUTSIDE)
			handle_outside_state(state, cmd, i);
		else if (state->state == INSIDE_SINGLE_QUOTE)
			handle_in_single_quote(state, cmd[i]);
		else if (state->state == INSIDE_DOUBLE_QUOTE)
			handle_in_double_quote(state, cmd, &i);
		i++;
	}
}

char	**parse_arguments(t_shell *shell, char *input)
{
	t_parse_state	state;

	state.args = malloc(ARG_ARR_SIZE * sizeof(char *));
	if (!state.args)
		return (NULL);
	init_arr(state.args, ARG_ARR_SIZE);
	state.arg = NULL;
	state.argc = 0;
	state.arg_size = ARG_ARR_SIZE;
	state.state = OUTSIDE;
	state.dollar_sign = 0;
	parse_argument_loop(&state, input);
	if (state.arg)
		state.args = add_arg(state.args, state.arg, \
				&state.argc, &state.arg_size);
	state.args[state.argc] = NULL;
	if (ft_strchr(input, '$') && state.dollar_sign == 0/*!ft_strchr(input, '\'')*/)
		handle_dollar_sign(*shell, &state.args);
	hande_tilde(&state.args, *shell, &shell->exit_code);
	return (state.args);
}
