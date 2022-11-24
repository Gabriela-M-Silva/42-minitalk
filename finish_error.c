/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finish_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/22 05:52:47 by gde-mora          #+#    #+#             */
/*   Updated: 2022/11/24 18:03:45 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minitalk.h"

void	finish_error(int flag)
{
	if (flag == 1)
	{
		ft_printf("Invalid arguments.\n");
		ft_printf("./client [PID] [message]\n");
	}
	else if (flag == 2)
		ft_printf("Error. Invalid pid or server response.\n");
	else if (flag == 3)
		ft_printf("Error. Invalid pid or client response.\n");
	exit(0);
}
