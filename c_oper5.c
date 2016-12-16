/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_oper5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 14:52:26 by jshi              #+#    #+#             */
/*   Updated: 2016/12/08 15:31:43 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	c_tanh(t_complex a)
{
	t_complex	b;

	b = c_exp(c_mult(a, c_make(2, 0)));
	return (c_div(c_sub(b, c_make(1, 0)), c_add(b, c_make(1, 0))));
}

t_complex	c_csch(t_complex a)
{
	t_complex	b;

	b = c_make(-a.re, -a.im);
	return (c_div(c_make(2, 0), c_sub(c_exp(a), c_exp(b))));
}

t_complex	c_sech(t_complex a)
{
	t_complex	b;

	b = c_make(-a.re, -a.im);
	return (c_div(c_make(2, 0), c_add(c_exp(a), c_exp(b))));
}

t_complex	c_coth(t_complex a)
{
	t_complex	b;

	b = c_exp(c_mult(a, c_make(2, 0)));
	return (c_div(c_add(b, c_make(1, 0)), c_sub(b, c_make(1, 0))));
}
