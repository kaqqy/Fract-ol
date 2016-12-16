/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_expr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 03:21:25 by jshi              #+#    #+#             */
/*   Updated: 2016/12/15 22:01:47 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	eval_expr(t_expr *expr, t_complex z, t_complex p, t_complex c, int ind)
{
	int		i;

	i = expr->size;
	while (i--)
	{
		if (expr->opers[i].type == 2)
			expr->vals[ind][i] = (*expr->opers[i].func2)(
					expr->vals[ind][expr->opers[i].ind1],
					expr->vals[ind][expr->opers[i].ind2]);
		else if (expr->opers[i].type == 1)
			expr->vals[ind][i] = (*expr->opers[i].func1)(
					expr->vals[ind][expr->opers[i].ind1]);
		else if (expr->opers[i].type == -1)
			expr->vals[ind][i] = z;
		else if (expr->opers[i].type == -2)
			expr->vals[ind][i] = p;
		else if (expr->opers[i].type == -3)
			expr->vals[ind][i] = c;
		else
			expr->vals[ind][i] = expr->opers[i].val;
	}
	return (expr->vals[ind][0]);
}
