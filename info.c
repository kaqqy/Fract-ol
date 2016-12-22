/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 21:21:41 by jshi              #+#    #+#             */
/*   Updated: 2016/12/21 21:22:36 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	disp_usage(t_env *env)
{
	ft_printf("Usage: ./fractol function starting_value bound iterations\n");
	exit_prog(env, "");
}

void	disp_info(void)
{
}
