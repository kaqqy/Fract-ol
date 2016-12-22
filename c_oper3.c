/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_oper3.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 03:06:51 by jshi              #+#    #+#             */
/*   Updated: 2016/12/19 23:03:21 by jshi             ###   ########.fr       */
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
	return ((t_complex){pow_e * cos(a.im), pow_e * sin(a.im)});
}

t_complex	c_sin(t_complex a)
{
	return (c_div(c_sub(c_exp((t_complex){-a.im, a.re}),
					c_exp((t_complex){a.im, -a.re})), (t_complex){0, 2}));
}

t_complex	c_cos(t_complex a)
{
	return (c_div(c_add(c_exp((t_complex){-a.im, a.re}),
					c_exp((t_complex){a.im, -a.re})), (t_complex){2, 0}));
}

t_complex	c_tan(t_complex a)
{
	t_complex	b;

	b = c_exp(c_mult(a, (t_complex){0, 2}));
	return (c_div(c_sub(b, (t_complex){1, 0}),
				c_mult(c_add(b, (t_complex){1, 0}), (t_complex){0, 1})));
}
