/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: abourdar <abourdar@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/24 08:20:46 by abourdar          #+#    #+#             */
/*   Updated: 2022/06/24 08:20:47 by abourdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	**g_env = NULL;

int	exit_program(t_list **cmd, t_list **token, int *i, t_data *env)
{
	if (*token != NULL)
	{
		*cmd = parsing(*token);
		if (*cmd != NULL)
		{
			*i = executer(*cmd, env);
		}
	}
	if ((*cmd) != NULL)
	{
		ft_lstclear(cmd, m_cmd_destroy);
		(*cmd) = NULL;
	}
	if ((*i) == 999)
	{
		(*i) = exec_last_ruturn_get();
		ft_putstr_fd("exit\n", STDERR_FILENO);
		return (0);
	}
	return (1);
}

int	start(t_data *env)
{
	char	*cmd_input;
	t_list	*token;
	t_list	*cmd;
	int		i;

	cmd = NULL;
	token = NULL;
	i = 0;
	signal(SIGINT, SIG_IGN);
	while (1)
	{
		signal(SIGINT, ctrl_c_handle);
		if (isatty(STDIN_FILENO))
			cmd_input = get_bytes_rl();
		else
			return (667);
		if (cmd_input == NULL)
			break ;
		token = process(cmd_input);
		if (!exit_program(&cmd, &token, &i, env))
			break ;
	}
	return (i);
}

int	main(int ac, char **av, char **envp)
{
	t_data	*env;
	int		status;

	signal(SIGQUIT, SIG_IGN);
	env = malloc(sizeof(t_data));
	ft_memset(env, 0, sizeof(t_data));
	status = 0;
	if (ac == 1 && av)
	{
		g_env = get_env(env, envp);
		status = start(env);
		if (status == 667)
		{
			status = -1;
			ft_putstr_fd("Error\n", STDERR_FILENO);
		}	
	}
	rl_clear_history();
	free_d_char(g_env);
	free(env);
	exit (status);
}
