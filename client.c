/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 21:22:54 by gde-mora          #+#    #+#             */
/*   Updated: 2022/11/22 04:53:48 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

//global PID
t_send	g_send;

void	send_bit(int i)
{
	if (g_send.msg[i] % 2 == 0)
	{
		kill(g_send.pid, SIGUSR2);
		g_send.msg[i] /= 2;
	}
	else if (g_send.msg[i] % 2 == 1)
	{
		g_send.msg[i] /= 2;
		kill(g_send.pid, SIGUSR1);
	}
}

void	send_signal()
{
	static int	i;
	static int	bits;

	if (bits == 8)
	{
		bits = 0;
		i++;
	}
	if (!g_send.msg[i] && bits == 0)
	{
		ft_putstr_fd("Process finished.\n", 1);
		exit (0);
	}
	if (bits < 8)
	{
		send_bit(i);
		bits++;
	}
}

void	handler_sigusr(int sigusr, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (sigusr == SIGUSR1)
		send_signal();
}

int main (int argc, char **argv) //manda um sinal, entra em pausa. Sai da pausa quando recebe um sinal do server (volta a funcionar)
{
	struct sigaction	sa;
	sigset_t			mask;

	if (argc != 3) //testar norminette
	{
		ft_printf("Invalid arguments.\n");
		ft_printf("./client [PID] [string]\n");
		exit (0);
	}
	g_send.pid = ft_atoi(argv[1]); // e se a atoi der erro? tem como?
	if (kill(g_send.pid, 0) == -1)
	{
		ft_printf("Error. Invalid pid\n");
		exit (0);
	}
	sigemptyset(&mask); //anotar significados p mask
	g_send.msg = argv[2];
	sa.sa_flags = SA_SIGINFO; //anotar p flags tbm
	sa.sa_mask = mask;
	sa.sa_sigaction = handler_sigusr;
	sigaction(SIGUSR1, &sa, NULL);
	send_signal();
	while (1)
		pause();
	return (0); //
}//diminuir linhas
