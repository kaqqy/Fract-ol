/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_expr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 00:32:23 by jshi              #+#    #+#             */
/*   Updated: 2016/12/08 16:18:26 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

/*
** Technically this function isn't correct with the absolute value
** Just don't use more than one absolute value
*/

static int	skip_group(char *str, int i)
{
	int		paren;
	int		abs;

	paren = 0;
	abs = 0;
	if (str[i] == ')')
		paren = 1;
	else
		abs = 1;
	while ((paren > 0 || abs > 0) && i-- > 0)
	{
		if (str[i] == '|')
			abs = 1 - abs;
		else if (str[i] == '(')
			paren--;
		else if (str[i] == ')')
			paren++;
	}
	return (i);
}

static int	find_oper(char *str, int len)
{
	int		i;
	int		ind1;
	int		ind2;
	int		ind3;

	i = len;
	ind1 = -1;
	ind2 = -1;
	ind3 = -1;
	while (i--)
	{
		if ((str[i] == '+' || str[i] == '-') && ind1 == -1)
			ind1 = i;
		if ((str[i] == '*' || str[i] == '/') && ind2 == -1)
			ind2 = i;
		if (str[i] == '^')
			ind3 = i;
		if (str[i] == ')' || str[i] == '|')
			i = skip_group(str, i);
	}
	if (ind1 != -1)
		return (ind1);
	else if (ind2 != -1)
		return (ind2);
	return (ind3);
}

int			parse_expr(char *str, t_expr *expr)
{
	int		ind;
	int		len;
	int		i;

	ind = expr->size;
	oper_arr_add(&expr->opers, &expr->size);
	len = ft_strlen(str);
	i = find_oper(str, len);
	if (i != -1)
		parse_expr2(str, expr, ind, i);
	else if (str[len - 1] == ')' || str[len - 1] == '|')
		parse_expr1(str, expr, ind, skip_group(str, len - 1));
	else
	{
		expr->opers[ind].type = 0;
		(str[0] == 'z') ? (expr->opers[ind].type = -1) : 0;
		(str[0] == 'p') ? (expr->opers[ind].type = -2) : 0;
		(str[0] == 'c') ? (expr->opers[ind].type = -3) : 0;
		if (expr->opers[ind].type == 0)
			parse_expr0(str, expr, ind, -1);
	}
	free(str);
	return (ind);
}

char		*clean_expr(char *str)
{
	int		i;
	int		j;
	int		len;

	len = ft_strlen(str);
	i = 0;
	j = 0;
	while (i < len)
	{
		if (str[i] == ' ')
			i++;
		else
			str[j++] = str[i++];
	}
	str[j] = '\0';
	while (j--)
		if (str[j] >= 'A' && str[j] <= 'Z')
			str[j] += 32;
	return (str);
}
