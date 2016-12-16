/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_fractal.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/09 21:13:12 by jshi              #+#    #+#             */
/*   Updated: 2016/12/15 22:26:08 by jshi             ###   ########.fr       */
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
void		draw_fractal(t_env *env)
{
	int			i;
	int			j;
	int			k;
	t_complex	z;
	t_complex	p;
	t_complex	c;
	t_complex	left;
	t_complex	right;

	mlx_clear_window(env->mlx, env->win);
	clear_image(env);
	i = -1;
	while (++i < WIN_WID)
	{
		j = -1;
		while (++j < WIN_LEN)
		{
			p = c_make(env->origin.re + j * env->pixel_len,
					env->origin.im + i * env->pixel_len);
			c = c_make(env->origin.re + env->cx * env->pixel_len,
					env->origin.im + env->cy * env->pixel_len);
			z = eval_expr(&env->start, (t_complex){0, 0}, p, c, 0);
			k = -1;
			while (++k < env->iter)
			{
				left = eval_expr(&env->ineq_l, z, p, c, 0);
				right = eval_expr(&env->ineq_r, z, p, c, 0);
				if ((env->comp == 0 && left.re >= right.re) ||
						(env->comp == 1 && left.re <= right.re) ||
						(env->comp == 2 && left.re > right.re) ||
						(env->comp == 3 && left.re < right.re))
					break ;
				z = eval_expr(&env->func, z, p, c, 0);
			}
			draw_point(env, j, i, get_color(30 * (k + env->color_rot)));
		}
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}
*/

static void	draw_partial(t_tdata *thread)
{
	t_env		*env;
	int			i;
	int			j;
	int			k;
	int			l;
	t_complex	z;
	t_complex	p;
	t_complex	c;
	t_complex	left;
	t_complex	right;

	env = thread->env;
	i = -1;
	while ((++i) * thread->count + thread->ind < WIN_LEN * WIN_WID)
	{
		j = (i * thread->count + thread->ind) / WIN_LEN;
		k = (i * thread->count + thread->ind) % WIN_LEN;
		p = c_make(env->origin.re + k * env->pixel_len,
				env->origin.im + j * env->pixel_len);
		c = c_make(env->origin.re + env->cx * env->pixel_len,
				env->origin.im + env->cy * env->pixel_len);
		z = eval_expr(&env->start, (t_complex){0, 0}, p, c, thread->ind);
		l = -1;
		while (++l < env->iter)
		{
			left = eval_expr(&env->ineq_l, z, p, c, thread->ind);
			right = eval_expr(&env->ineq_r, z, p, c, thread->ind);
			if ((env->comp == 0 && left.re >= right.re) ||
					(env->comp == 1 && left.re <= right.re) ||
					(env->comp == 2 && left.re > right.re) ||
					(env->comp == 3 && left.re < right.re))
				break ;
			z = eval_expr(&env->func, z, p, c, thread->ind);
		}
		draw_point(env, k, j, get_color(30 * (l + env->color_rot)));
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
		thread->count = env->num_threads;
		pthread_create(&env->threads[i], NULL, (void*)draw_partial, thread);
	}
	i = -1;
	while (++i < env->num_threads)
		pthread_join(env->threads[i], NULL);
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}
