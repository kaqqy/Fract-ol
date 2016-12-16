/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_oper3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 03:06:51 by jshi              #+#    #+#             */
/*   Updated: 2016/12/08 15:29:57 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	c_cpy(t_complex a)
{
	return (a);
}

t_complex	c_exp(t_complex a)
{
	double	pow_e;

	pow_e = pow(M_E, a.re);
	return (c_make(pow_e * cos(a.im), pow_e * sin(a.im)));
}

t_complex	c_sin(t_complex a)
{
	t_complex	b;
	t_complex	c;

	b = c_make(-a.im, a.re);
	c = c_make(a.im, -a.re);
	return (c_div(c_sub(c_exp(b), c_exp(c)), c_make(0, 2)));
}

t_complex	c_cos(t_complex a)
{
	t_complex	b;
	t_complex	c;

	b = c_make(-a.im, a.re);
	c = c_make(a.im, -a.re);
	return (c_div(c_add(c_exp(b), c_exp(c)), c_make(2, 0)));
}

t_complex	c_tan(t_complex a)
{
	t_complex	b;

	b = c_exp(c_mult(a, c_make(0, 2)));
	return (c_div(c_sub(b, c_make(1, 0)),
				c_mult(c_add(b, c_make(1, 0)), c_make(0, 1))));
}
