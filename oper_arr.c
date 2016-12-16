/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   oper_arr.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/06 23:14:00 by jshi              #+#    #+#             */
/*   Updated: 2016/12/07 01:18:49 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

t_oper	*oper_arr_new(void)
{
	return ((t_oper*)malloc(sizeof(t_oper) * 4));
}

void	oper_arr_add(t_oper **arr, int *size)
{
	t_oper	*realloc;
	int		cpy;
	int		limit;

	cpy = *size;
	limit = 1;
	while (cpy > 1)
	{
		cpy >>= 1;
		limit <<= 1;
	}
	if (*size == limit && limit > 3)
	{
		if (!(realloc = (t_oper*)malloc(sizeof(*realloc) * 2 * limit)))
			return ;
		ft_memcpy(realloc, *arr, sizeof(*realloc) * *size);
		free(*arr);
		*arr = realloc;
	}
	(*size)++;
}
