/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_oper6.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 17:17:50 by jshi              #+#    #+#             */
/*   Updated: 2016/12/19 23:10:23 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	c_re(t_complex a)
{
	return ((t_complex){a.re, 0});
}

t_complex	c_im(t_complex a)
{
	return ((t_complex){a.im, 0});
}
