#include "minishell.h"

void prompt(t_shell *shell)
{

		shell->input = readline("> ");
		if(shell->input != NULL && !is_empty_str(shell->input))
		{
			add_history(shell->input);
			shell->arr_input = parse_arguments(shell->input);
		}
}
