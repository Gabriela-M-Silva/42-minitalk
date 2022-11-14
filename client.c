/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   client.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 21:22:54 by gde-mora          #+#    #+#             */
/*   Updated: 2022/11/14 23:38:32 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler_sigusr(int sigusr, siginfo_t *info, void *context)
{
	(void)context;
	(void)info;
	if (sigusr == SIGUSR1)
	{
		ft_putstr_fd("Entendi, é 't'\n", 1);
		exit (0);
	}
	else if (sigusr == SIGUSR2)
	{
		ft_putstr_fd("Entendi, não é 't'\n", 1);
		exit (0);
	}
}

int main (int argc, char **argv)
{
	struct sigaction	sa;
	int pid; //teste

	sa.sa_sigaction = handler_sigusr;
	if (argc != 3)
	{
		ft_printf("Invalid arguments.\n");
		ft_printf("./client [PID] [string]\n");
		exit (0);
	}
	pid = ft_atoi(argv[1]);
	if (argv[2][0] == 't')
		kill(pid, SIGUSR1);
	else
		kill(pid, SIGUSR2);
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause();
	return (0); 
} 
