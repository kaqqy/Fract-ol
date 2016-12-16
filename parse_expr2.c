/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expr2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/08 15:35:45 by jshi              #+#    #+#             */
/*   Updated: 2016/12/08 17:17:41 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		parse_expr2(char *str, t_expr *expr, int ind, int i)
{
	int		len;

	len = ft_strlen(str);
	expr->opers[ind].type = 2;
	expr->opers[ind].ind1 = parse_expr(ft_strsub(str, 0, i), expr);
	expr->opers[ind].ind2 = parse_expr(ft_strsub(str, i + 1, len - i - 1),
			expr);
	(str[i] == '+') ? (expr->opers[ind].func2 = &c_add) : 0;
	(str[i] == '-') ? (expr->opers[ind].func2 = &c_sub) : 0;
	(str[i] == '*') ? (expr->opers[ind].func2 = &c_mult) : 0;
	(str[i] == '/') ? (expr->opers[ind].func2 = &c_div) : 0;
	(str[i] == '^') ? (expr->opers[ind].func2 = &c_pow) : 0;
}

void		parse_expr1(char *str, t_expr *expr, int ind, int i)
{
	expr->opers[ind].type = 1;
	expr->opers[ind].ind1 = parse_expr(ft_strsub(str, i + 1,
				ft_strlen(str) - i - 2), expr);
	(str[0] == '|') ? (expr->opers[ind].func1 = &c_mag) : 0;
	(str[0] == '(') ? (expr->opers[ind].func1 = &c_cpy) : 0;
	(ft_strnequ(str, "sqrt(", 5)) ? (expr->opers[ind].func1 = &c_sqrt) : 0;
	(ft_strnequ(str, "ln(", 3)) ? (expr->opers[ind].func1 = &c_ln) : 0;
	(ft_strnequ(str, "exp(", 4)) ? (expr->opers[ind].func1 = &c_exp) : 0;
	(ft_strnequ(str, "sin(", 4)) ? (expr->opers[ind].func1 = &c_sin) : 0;
	(ft_strnequ(str, "cos(", 4)) ? (expr->opers[ind].func1 = &c_cos) : 0;
	(ft_strnequ(str, "tan(", 4)) ? (expr->opers[ind].func1 = &c_tan) : 0;
	(ft_strnequ(str, "csc(", 4)) ? (expr->opers[ind].func1 = &c_csc) : 0;
	(ft_strnequ(str, "sec(", 4)) ? (expr->opers[ind].func1 = &c_sec) : 0;
	(ft_strnequ(str, "cot(", 4)) ? (expr->opers[ind].func1 = &c_cot) : 0;
	(ft_strnequ(str, "sinh(", 5)) ? (expr->opers[ind].func1 = &c_sinh) : 0;
	(ft_strnequ(str, "cosh(", 5)) ? (expr->opers[ind].func1 = &c_cosh) : 0;
	(ft_strnequ(str, "tanh(", 5)) ? (expr->opers[ind].func1 = &c_tanh) : 0;
	(ft_strnequ(str, "csch(", 5)) ? (expr->opers[ind].func1 = &c_csch) : 0;
	(ft_strnequ(str, "sech(", 5)) ? (expr->opers[ind].func1 = &c_sech) : 0;
	(ft_strnequ(str, "coth(", 5)) ? (expr->opers[ind].func1 = &c_coth) : 0;
	(ft_strnequ(str, "re(", 3)) ? (expr->opers[ind].func1 = &c_re) : 0;
	(ft_strnequ(str, "im(", 3)) ? (expr->opers[ind].func1 = &c_im) : 0;
}

void		parse_expr0(char *str, t_expr *expr, int ind, int i)
{
	double	val;
	int		dot;
	int		len;

	val = 0.0;
	dot = -1;
	len = ft_strlen(str);
	while (++i < len)
	{
		if (str[i] >= '0' && str[i] <= '9')
		{
			val = val * 10 + str[i] - '0';
			if (dot >= 0)
				dot++;
		}
		else if (str[i] == '.')
			dot = 0;
	}
	while (dot-- > 0)
		val /= 10;
	(str[len - 1] == 'i' && val == 0.0) ? (val = 1.0) : 0;
	if (str[len - 1] == 'i')
		expr->opers[ind].val = c_make(0, val);
	else
		expr->opers[ind].val = c_make(val, 0);
}
