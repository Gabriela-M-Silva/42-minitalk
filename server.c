/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 21:23:19 by gde-mora          #+#    #+#             */
/*   Updated: 2022/11/22 05:13:06 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_pow(int basis, int exp)
{
	int	i;
	int number;

	i = 0;
	number = 1;
	while (i != exp) //
	{
		number = number * basis;
		i++;
	}
	return (number);
}                      //void	add_char_to_str

void	add_bit_to_byte(int boolean)
{
	static int	number;
	static int	bits;

	number += boolean * ft_pow(2, bits);
	bits++;
	if (bits == 8)
	{
	//	if (number == '\0')
	//		ft_putchar_fd('\n', 1);
	//	else
		ft_putchar_fd(number, 1);
		bits = 0;
		number = 0;
	}
}

void	handler_sigusr(int sigusr, siginfo_t *info, void *context)
{
	//static int	counter;   //usar isso?

	(void)context;
	if (sigusr == SIGUSR1)
	{
		add_bit_to_byte(1);
	//	counter = 0;
		kill(info->si_pid, SIGUSR1);
	}
	else if (sigusr == SIGUSR2)
	{
	/*	if (counter++ == 8)
			ft_putchar_fd('\n', 1);
		else
		{*/
			add_bit_to_byte(0);
			kill(info->si_pid, SIGUSR1);
	//	}
	}
}

int main(void)
{
	struct sigaction	sa;
	sigset_t			mask;

	sigemptyset(&mask);
	sa.sa_flags = SA_SIGINFO;
	sa.sa_mask = mask;
	sa.sa_sigaction = handler_sigusr;
	ft_printf("PID: %d\n", getpid());
	sigaction(SIGUSR1, &sa, NULL);
	sigaction(SIGUSR2, &sa, NULL);
	while (1)
		pause ();
	return (0);
}
