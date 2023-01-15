/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 11:34:31 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 11:34:39 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_bytes_rl(void)
{
	char	*input;
	char	*prompt;
	char	*tmp;

	prompt = prompt_str();
	input = readline(prompt);
	if (input != NULL)
	{
		add_history(input);
		tmp = input;
		input = ft_strjoin(input, "\n");
		free(tmp);
		free(prompt);
		return (input);
	}
	free(prompt);
	ft_putstr_fd("exit\n", STDERR_FILENO);
	return (NULL);
}

t_list	*process(char *cmd_input)
{
	t_list	*token;
	t_list	*token_cheked;

	signal(SIGINT, SIG_IGN);
	token = NULL;
	token_cheked = NULL;
	token = lexer(cmd_input);
	free(cmd_input);
	if (token == NULL)
		return (NULL);
	token_cheked = check_syntax(token);
	if (token_cheked == NULL)
		return (NULL);
	return (token_cheked);
}

void	init_env(t_data *env)
{
	env->path_i = 0;
	env->fds = malloc(sizeof(t_red_fds));
	ft_memset(env->fds, 0, sizeof(t_red_fds));
}

int	executer(t_list *cmd, t_data *env)
{
	int	i;

	i = 0;
	init_env(env);
	if (p_cmd_struct(cmd)->type == CMD_PIPELINE)
			i = exec_pipe(cmd, env);
	else
		i = exec_scmd(cmd, env);
	if (i != 999)
		exec_last_return_set(i);
	return (i);
}

int	print_error(char *shell_name, char *cmd, char *error)
{
	if (shell_name)
		ft_putstr_fd(shell_name, STDERR_FILENO);
	if (cmd)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(cmd, STDERR_FILENO);
	}
	if (error)
	{
		ft_putstr_fd(": ", STDERR_FILENO);
		ft_putstr_fd(error, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	return (ERROR);
}
