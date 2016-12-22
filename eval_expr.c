/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   eval_expr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 03:21:25 by jshi              #+#    #+#             */
/*   Updated: 2016/12/21 05:02:44 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_complex	eval_expr(t_expr *expr, t_triple vars, int ind)
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
			expr->vals[ind][i] = vars.z;
		else if (expr->opers[i].type == -2)
			expr->vals[ind][i] = vars.p;
		else if (expr->opers[i].type == -3)
			expr->vals[ind][i] = vars.c;
		else
			expr->vals[ind][i] = expr->opers[i].val;
	}
	return (expr->vals[ind][0]);
}
