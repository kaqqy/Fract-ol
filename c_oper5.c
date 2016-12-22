/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_oper5.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 14:52:26 by jshi              #+#    #+#             */
/*   Updated: 2016/12/20 04:37:37 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	c_tanh(t_complex a)
{
	t_complex	b;

	b = c_exp(c_mult(a, (t_complex){2, 0}));
	return (c_div(c_sub(b, (t_complex){1, 0}), c_add(b, (t_complex){1, 0})));
}

t_complex	c_csch(t_complex a)
{
	return (c_div((t_complex){2, 0}, c_sub(c_exp(a),
					c_exp((t_complex){-a.re, -a.im}))));
}

t_complex	c_sech(t_complex a)
{
	return (c_div((t_complex){2, 0},
				c_add(c_exp(a), c_exp((t_complex){-a.re, -a.im}))));
}

t_complex	c_coth(t_complex a)
{
	t_complex	b;

	b = c_exp(c_mult(a, (t_complex){2, 0}));
	return (c_div(c_add(b, (t_complex){1, 0}), c_sub(b, (t_complex){1, 0})));
}
