/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 21:13:12 by jshi              #+#    #+#             */
/*   Updated: 2016/12/21 20:50:24 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static void	clear_image(t_env *env)
{
	int		i;
	int		j;
	int		k;

	i = -1;
	while (++i < WIN_WID)
	{
		j = -1;
		while (++j < WIN_LEN)
		{
			k = -1;
			while (++k < env->bpp)
				env->data[env->sl * i + env->bpp * j + k] = 0;
		}
	}
}

static int	get_color(int n)
{
	n %= 1530;
	return ((0xff << ((2 - n / 510) * 8)) + (255 -
			MIN(n % 510, (1530 - n) % 510)) * (1 << (8 * ((n / 255) % 3))));
}

/*
** a = {i, j, k, l, thread->ind}
** b = {z, p, c, z_cpy, left, right}
*/

static void	draw_partial2(t_env *env, int a[5], t_complex b[6])
{
	a[3] = -1;
	while (++a[3] < env->iter)
	{
		b[4] = eval_expr(&env->ineq_l, (t_triple){b[0], b[1], b[2]}, a[4]);
		b[5] = eval_expr(&env->ineq_r, (t_triple){b[0], b[1], b[2]}, a[4]);
		if ((env->comp % 2 == 0 && b[4].re > b[5].re) ||
				(env->comp % 2 == 1 && b[4].re < b[5].re) ||
				(env->comp < 2 && b[4].re == b[5].re))
			break ;
		b[3] = eval_expr(&env->func, (t_triple){b[0], b[1], b[2]}, a[4]);
		if (ABS(b[3].re - b[0].re) <= env->prec * env->pixel_len &&
				ABS(b[3].im - b[0].im) <= env->prec * env->pixel_len)
		{
			a[3] = env->iter;
			break ;
		}
		b[0] = b[3];
	}
}

static void	draw_partial(t_tdata *thread)
{
	t_env		*env;
	int			a[5];
	t_complex	b[6];

	env = thread->env;
	a[0] = -1;
	a[4] = thread->ind;
	b[0] = (t_complex){0, 0};
	while ((++a[0]) * env->num_threads + a[4] < WIN_LEN * WIN_WID)
	{
		a[1] = (a[0] * env->num_threads + a[4]) / WIN_LEN;
		a[2] = (a[0] * env->num_threads + a[4]) % WIN_LEN;
		b[1] = (t_complex){env->origin.re + a[2] * env->pixel_len,
				env->origin.im + a[1] * env->pixel_len};
		b[2] = env->c;
		b[0] = eval_expr(&env->start, (t_triple){b[0], b[1], b[2]}, a[4]);
		draw_partial2(env, a, b);
		draw_point(env, a[2], a[1], (a[3] == env->iter) ? 0 :
				get_color(30 * (a[3] + env->color_rot)));
	}
	free(thread);
}

void		draw_fractal(t_env *env)
{
	int		i;
	t_tdata	*thread;

	mlx_clear_window(env->mlx, env->win);
	clear_image(env);
	i = -1;
	while (++i < env->num_threads)
	{
		thread = (t_tdata*)malloc(sizeof(*thread));
		thread->env = env;
		thread->ind = i;
		pthread_create(&env->threads[i], NULL, (void*)draw_partial, thread);
	}
	i = -1;
	while (++i < env->num_threads)
		pthread_join(env->threads[i], NULL);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}
