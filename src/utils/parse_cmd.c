/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cmd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmakkone <jmakkone@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/29 08:45:08 by jmakkone          #+#    #+#             */
/*   Updated: 2024/09/03 13:14:41 by mpellegr         ###   ########.fr       */
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

int	ft_is_uppercase(char c)
{
	if (c < 'A' || c > 'Z')
		return (0);
	return (1);
}

char	**parse_arguments(t_shell shell)
{
	t_parse_state	state;

	state.args = malloc(ARG_ARR_SIZE * sizeof(char *));
	if (!state.args)
		return (NULL);
	state.arg = NULL;
	state.argc = 0;
	state.arg_size = ARG_ARR_SIZE;
	state.state = OUTSIDE;
	if (ft_strchr(shell.input, '$') && !ft_strchr(shell.input, '\''))
	{
		char	**input_arr;
		int		i;
		int		j;
		int		k;

		input_arr = ft_split(shell.input, '$');
		i = 0;
		k = 0;
		while (input_arr[i])
		{
			j = 0;
			while (shell.envp[j])
			{
				if (!ft_strncmp(shell.envp[j], input_arr[i], ft_strlen(input_arr[i])))
				{
					int len = ft_strlen(input_arr[i]);
					free(input_arr[i]);
					input_arr[i] = (char *)malloc(sizeof(char) * (ft_strlen(shell.envp[j]) - len));
					while (shell.envp[j][len + 1])
					{
						input_arr[i][k] = shell.envp[j][len + 1];
						k++;
						len++;
					}
				}
				j++;
			}
			i++;
		}
		i = 0;
		free(shell.input);
		shell.input = ft_strdup(input_arr[i]);
		while (input_arr[++i])
			shell.input = ft_strjoin(shell.input, input_arr[i]);
		/*
		char	*var;
		int		start;
		int		i;
		int		var_len;
	
		start = 0;
		var_len = 0;
		while (shell.input[start] != '$')
			start++;
		start++;
		i = start;
		while (shell.input[i] && ft_is_uppercase(shell.input[i]))
		{
			i++;
			var_len++;
		}
		var = (char *)malloc(sizeof(char) * (var_len + 1));
		i = 0;
		while ((shell.input)[start])
			var[i++] = (shell.input)[start++];
		var[i] = '\0';
		i = 0;
		while ((shell.envp)[i] && ft_strncmp((shell.envp)[i], var, ft_strlen(var)))
			i++;
		free(shell.input);
		shell.input = (char *)malloc(sizeof(char) * (ft_strlen((shell.envp)[i]) - var_len + 1));
		int j = 0;
		var_len++;
		while((shell.envp)[i][var_len])
			shell.input[j++] = (shell.envp)[i][var_len++];*/
	}
	parse_argument_loop(&state, &(shell.input));
	//free(temp_cmd);
	if (state.arg)
		state.args = add_arg(state.args, state.arg, \
				&state.argc, &state.arg_size);
	state.args[state.argc] = NULL;
	return (state.args);
}
