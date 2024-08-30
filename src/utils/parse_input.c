#include "minishell.h"

static void	quotes_and_esc(char ****cmd_ptr, int *in_quote, char *quote_char)
{
	if (*in_quote && ****cmd_ptr == *quote_char)
	{
		*in_quote = 0;
		*quote_char = '\0';
	}
	else if (!*in_quote)
	{
		*in_quote = 1;
		*quote_char = ****cmd_ptr;
	}
	(***cmd_ptr)++;
}

static void	process_cmd(char ***cmd_ptr, char (*buffer)[], int *len)
{
	int		in_quote;
	int		done;
	char	quote_char;

	in_quote = 0;
	done = 0;
	quote_char = '\0';
	while (***cmd_ptr && !done)
	{
		if (***cmd_ptr == '"' || ***cmd_ptr == '\'' || ***cmd_ptr == '\\')
			quotes_and_esc(&cmd_ptr, &in_quote, &quote_char);
		else if (!in_quote && ***cmd_ptr == ' ' && *(**cmd_ptr - 1) != '\\')
			done = 1;
		else
		{
			(*buffer)[(*len)++] = ***cmd_ptr;
			(**cmd_ptr)++;
		}
	}
}

static int	extract_token(char **cmd_ptr, char **token)
{
	char	buffer[1024];
	int		len;

	len = 0;
	while (**cmd_ptr && **cmd_ptr == ' ')
		(*cmd_ptr)++;
	process_cmd(&cmd_ptr, &buffer, &len);
	if (len == 0)
	{
		*token = NULL;
		return (0);
	}
	buffer[len] = '\0';
	*token = ft_strdup(buffer);
	if (**cmd_ptr)
		(*cmd_ptr)++;
	return (1);
}

char	**parse_input(char *cmd)
{
	char	**arr;
	char	*token;
	int		token_count;
	int		i;
	char	*cmd_ptr;

	token_count = 0;
	i = 0;
	cmd_ptr = cmd;
	while (extract_token(&cmd_ptr, &token) != 0)
	{
		token_count++;
		free(token);
	}
	arr = (char **)malloc(sizeof(char *) * (token_count + 1));
	if (!arr)
		return (NULL);
	cmd_ptr = cmd;
	while (extract_token(&cmd_ptr, &token) != 0)
		arr[i++] = token;
	arr[i] = NULL;
	free(token);
	return (arr);
}

