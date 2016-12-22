/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   c_oper2.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/05 17:42:15 by jshi              #+#    #+#             */
/*   Updated: 2016/12/19 22:55:38 by jshi             ###   ########.fr       */
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
		return ((t_complex){1, 0});
	if (a.re == 0.0 && a.im == 0.0 && b.re > 0.0)
		return ((t_complex){0, 0});
	c = c_mult(c_ln(a), b);
	pow_e = pow(M_E, c.re);
	return ((t_complex){pow_e * cos(c.im), pow_e * sin(c.im)});
}

t_complex	c_sqrt(t_complex a)
{
	double		angle;
	double		len;

	angle = atan2(a.im, a.re) / 2;
	len = sqrt(sqrt(a.re * a.re + a.im * a.im));
	return ((t_complex){len * cos(angle), len * sin(angle)});
}

t_complex	c_ln(t_complex a)
{
	return ((t_complex){log(mag(a)), atan2(a.im, a.re)});
}
