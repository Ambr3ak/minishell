/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 08:36:37 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 08:37:02 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	no_space_tok(t_list **token, char **cmd_str)
{
	char	*free_str;

	while (tok_struct(*token)->flag & TOKEN_CONNECTED)
	{
		free_str = *cmd_str;
		*cmd_str = ft_strjoin(*cmd_str, tok_struct((*token)->next)->tk);
		free(free_str);
		if (*cmd_str == NULL)
			return (print_error(MINISHELL, NULL, ERROR_MEMORY));
		*token = (*token)->next;
	}
	return (0);
}

int	lst_size(t_list *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		if (!(tok_struct(lst)->flag & TOKEN_CONNECTED))
			i++;
		lst = lst->next;
	}
	return (i);
}

int	nb_less(char **token)
{
	int	i;
	int	nb;

	i = 0 ;
	nb = 0;
	while (token[i])
	{
		if (token[i][0] == '\0')
			nb++;
		i++;
	}
	return (i - nb);
}

char	**del_empty_token(char ***token)
{
	char	**new_token;
	int		i;
	int		j;

	new_token = malloc(sizeof(char *) * (nb_less(*token) + 1));
	i = 0;
	j = 0;
	while ((*token)[i])
	{
		if ((*token)[i][0] != '\0')
		{
			new_token[j] = ft_strdup((*token)[i]);
			j++;
		}
		i++;
	}
	new_token[j] = NULL;
	free_d_char(*token);
	return (new_token);
}

char	**token_to_array(int *argc, t_list *scmd)
{
	char	**token;
	t_list	*tmp;
	int		size;
	int		i;

	size = init_size(scmd, argc);
	token = malloc(sizeof(char *) * (size + 1));
	token[size] = NULL;
	tmp = scmd;
	i = 0;
	while (tmp)
	{
		token[i] = ft_strdup(tok_struct(tmp)->tk);
		if (no_space_tok(&tmp, &token[i]) == ERROR_LEXER)
		{
			free_d_char(token);
			return (NULL);
		}
		i++;
		tmp = tmp->next;
	}
	token = del_empty_token(&token);
	return (token);
}
