/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minitalk.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gde-mora <gde-mora@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/01 01:16:23 by gde-mora          #+#    #+#             */
/*   Updated: 2022/11/23 03:31:17 by gde-mora         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINITALK_H
# define MINITALK_H

# include "./libft/libft.h"
# include "signal.h"

# define ERROR_ARG 1
# define ERROR_PID_C 2
# define ERROR_PID_S 3

typedef struct s_send
{
	int		pid;
	char	*msg;
}	t_send;

void	finish_error(int flag);

#endif