/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_oper4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 14:35:36 by jshi              #+#    #+#             */
/*   Updated: 2016/12/19 23:09:44 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	c_csc(t_complex a)
{
	return (c_div((t_complex){0, 2}, c_sub(c_exp((t_complex){-a.im, a.re}),
					c_exp((t_complex){a.im, -a.re}))));
}

t_complex	c_sec(t_complex a)
{
	return (c_div((t_complex){2, 0}, c_add(c_exp((t_complex){-a.im, a.re}),
					c_exp((t_complex){a.im, -a.re}))));
}

t_complex	c_cot(t_complex a)
{
	t_complex	b;

	b = c_exp(c_mult(a, (t_complex){0, 2}));
	return (c_div(c_mult(c_add(b, (t_complex){1, 0}), (t_complex){0, 1}),
				c_sub(b, (t_complex){1, 0})));
}

t_complex	c_sinh(t_complex a)
{
	return (c_div(c_sub(c_exp(a), c_exp((t_complex){-a.re, -a.im})),
				(t_complex){2, 0}));
}

t_complex	c_cosh(t_complex a)
{
	return (c_div(c_add(c_exp(a), c_exp((t_complex){-a.re, -a.im})),
				(t_complex){2, 0}));
}
