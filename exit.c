/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 17:05:19 by jshi              #+#    #+#             */
/*   Updated: 2016/12/08 21:05:16 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Should probably free everything in env
*/

void	exit_prog(t_env *env, char *msg)
{
	(void)env;
	ft_putstr_fd(msg, 2);
	*msg ? exit(1) : exit(0);
}
