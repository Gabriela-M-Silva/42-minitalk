/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 21:23:19 by gde-mora          #+#    #+#             */
/*   Updated: 2022/11/14 23:36:53 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	handler_sigusr(int sigusr, siginfo_t *info, void *context)
{
	(void)context;
	if (sigusr == SIGUSR1)
	{
		ft_putstr_fd("É 't'\n", 1);
//		ft_printf("%d\n", info->si_pid);
		kill(info->si_pid, SIGUSR1); //pegar o pid
	}
	else if (sigusr == SIGUSR2)
	{
		ft_putstr_fd("Não é 't'\n", 1);
//		ft_printf("%d\n", info->si_pid); //ta pegando o pid
		kill(info->si_pid, SIGUSR2);
	}
}

int main(void)
{
	struct sigaction sa;

	sa.sa_flags = SA_SIGINFO;
	sa.sa_sigaction = handler_sigusr;
	ft_printf("PID: %d\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause ();
	return (0);
}
