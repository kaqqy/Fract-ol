/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_oper4.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 14:35:36 by jshi              #+#    #+#             */
/*   Updated: 2016/12/08 15:30:25 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	c_csc(t_complex a)
{
	t_complex	b;
	t_complex	c;

	b = c_make(-a.im, a.re);
	c = c_make(a.im, -a.re);
	return (c_div(c_make(0, 2), c_sub(c_exp(b), c_exp(c))));
}

t_complex	c_sec(t_complex a)
{
	t_complex	b;
	t_complex	c;

	b = c_make(-a.im, a.re);
	c = c_make(a.im, -a.re);
	return (c_div(c_make(2, 0), c_add(c_exp(b), c_exp(c))));
}

t_complex	c_cot(t_complex a)
{
	t_complex	b;

	b = c_exp(c_mult(a, c_make(0, 2)));
	return (c_div(c_mult(c_add(b, c_make(1, 0)), c_make(0, 1)),
				c_sub(b, c_make(1, 0))));
}

t_complex	c_sinh(t_complex a)
{
	t_complex	b;

	b = c_make(-a.re, -a.im);
	return (c_div(c_sub(c_exp(a), c_exp(b)), c_make(2, 0)));
}

t_complex	c_cosh(t_complex a)
{
	t_complex	b;

	b = c_make(-a.re, -a.im);
	return (c_div(c_add(c_exp(a), c_exp(b)), c_make(2, 0)));
}
