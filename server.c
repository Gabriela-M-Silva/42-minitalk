/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   server.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/14 21:23:19 by gde-mora          #+#    #+#             */
/*   Updated: 2022/11/23 03:30:39 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

int	ft_pow(int basis, int exp)
{
	int	i;
	int	number;

	i = 0;
	number = 1;
	while (i != exp)
	{
		number = number * basis;
		i++;
	}
	return (number);
}

void	add_char_to_str(char c)
{
	static char	*str;
	char		*aux;	

	if (!str && c == '\0')
		return ;
	else if (c == '\0')
	{
		ft_printf("%s\n", str);
		free(str);
		str = NULL;
	}
	else
	{
		aux = malloc(2);
		aux[0] = c;
		aux[1] = '\0';
		str = ft_strjoin_gnl(str, aux);
		free(aux);
	}
}

void	add_bit_to_byte(int boolean)
{
	static int	number;
	static int	bits;

	number += boolean * ft_pow(2, bits);
	bits++;
	if (bits == 8)
	{
		add_char_to_str(number);
		bits = 0;
		number = 0;
	}
}

void	handler_sigusr(int sigusr, siginfo_t *info, void *context)
{
	(void)context;
	if (sigusr == SIGUSR1)
	{
		add_bit_to_byte(1);
		if (kill(info->si_pid, SIGUSR1) == -1)
			finish_error(ERROR_PID_S);
	}
	else if (sigusr == SIGUSR2)
	{
		add_bit_to_byte(0);
		if (kill(info->si_pid, SIGUSR1) == -1)
			finish_error(ERROR_PID_S);
	}
}

int	main(void)
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
