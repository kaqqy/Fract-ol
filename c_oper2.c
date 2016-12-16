/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_oper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 17:42:15 by jshi              #+#    #+#             */
/*   Updated: 2016/12/15 01:43:31 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

double		mag(t_complex a)
{
	return (sqrt(a.re * a.re + a.im * a.im));
}

t_complex	c_mag(t_complex a)
{
	return ((t_complex){sqrt(a.re * a.re + a.im * a.im), 0});
}

t_complex	c_pow(t_complex a, t_complex b)
{
	t_complex	c;
	double		pow_e;

	if (a.re == 0.0 && a.im == 0.0 && b.re == 0.0 && b.im == 0.0)
		return (c_make(1, 0));
	if (a.re == 0.0 && a.im == 0.0 && b.re > 0.0)
		return (c_make(0, 0));
	c = c_mult(c_ln(a), b);
	pow_e = pow(M_E, c.re);
	return (c_make(pow_e * cos(c.im), pow_e * sin(c.im)));
}

t_complex	c_sqrt(t_complex a)
{
	double		angle;
	double		len;

	angle = atan2(a.im, a.re);
	angle /= 2;
	len = mag(a);
	len = sqrt(len);
	return (c_make(len * cos(angle), len * sin(angle)));
}

t_complex	c_ln(t_complex a)
{
	return ((t_complex){log(mag(a)), atan2(a.im, a.re)});
}
