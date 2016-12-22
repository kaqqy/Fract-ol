/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_oper1.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 17:33:35 by jshi              #+#    #+#             */
/*   Updated: 2016/12/21 20:06:08 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	c_add(t_complex a, t_complex b)
{
	return ((t_complex){a.re + b.re, a.im + b.im});
}

t_complex	c_sub(t_complex a, t_complex b)
{
	return ((t_complex){a.re - b.re, a.im - b.im});
}

t_complex	c_mult(t_complex a, t_complex b)
{
	return ((t_complex){a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re});
}

t_complex	c_div(t_complex a, t_complex b)
{
	double		d;

	d = b.re * b.re + b.im * b.im;
	return ((t_complex){(a.re * b.re + a.im * b.im) / d,
			(a.im * b.re - a.re * b.im) / d});
}
