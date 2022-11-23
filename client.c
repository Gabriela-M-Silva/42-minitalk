/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 21:22:54 by gde-mora          #+#    #+#             */
/*   Updated: 2022/11/23 03:29:11 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

//global PID
t_send	g_send;

void	send_null_byte(int flag)
{
	static int	bits;

	if (bits != 8)
	{
		bits++;
		if (kill(g_send.pid, SIGUSR2) == -1)
			finish_error(ERROR_PID_C);
	}
	else
	{
		if (flag == 1)
		{
			ft_putstr_fd("Invalid char in message.\n", 1);
			ft_putstr_fd("Process interrupted with error.\n", 1);
		}
		else
			ft_putstr_fd("Process finished.\n", 1);
		exit (0);
	}
}

void	send_bit(int i)
{
	if (g_send.msg[i] % 2 == 0)
	{
		g_send.msg[i] /= 2;
		if (kill(g_send.pid, SIGUSR2) == -1)
			finish_error(ERROR_PID_C);
	}
	else if (g_send.msg[i] % 2 == 1)
	{
		g_send.msg[i] /= 2;
		if (kill(g_send.pid, SIGUSR1) == -1)
			finish_error(ERROR_PID_C);
	}
}

void	send_signal(void)
{
	static int	i;
	static int	bits;

	if (bits == 8)
	{
		bits = 0;
		i++;
	}
	if (g_send.msg[i] < 0 && bits == 0)
		send_null_byte(1);
	else if (!g_send.msg[i] && bits == 0)
		send_null_byte(0);
	else if (bits < 8)
	{
		bits++;
		send_bit(i);
	}
}

void	handler_sigusr(int sigusr, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (sigusr == SIGUSR1)
		send_signal();
}

int	main(int argc, char **argv)
{
	struct sigaction	sa;
	sigset_t			mask;

	if (argc != 3)
		finish_error(ERROR_ARG);
	g_send.pid = ft_atoi(argv[1]);
	sigemptyset(&mask);
	g_send.msg = argv[2];
	sa.sa_flags = SA_SIGINFO;
	sa.sa_mask = mask;
	sa.sa_sigaction = handler_sigusr;
	sigaction(SIGUSR1, &sa, NULL);
	send_signal();
	while (1)
		pause();
	return (0);
}
