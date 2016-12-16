/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 23:19:35 by jshi              #+#    #+#             */
/*   Updated: 2016/12/15 22:52:12 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			motion_hook(int x, int y, t_env *env)
{
	env->cx = x;
	env->cy = y;
	draw_fractal(env);
	return (0);
}

int			key_release_hook(int k, t_env *env)
{
	if (k == 123)
		env->origin.re -= env->pixel_len * 100;
	else if (k == 124)
		env->origin.re += env->pixel_len * 100;
	else if (k == 125)
		env->origin.im += env->pixel_len * 100;
	else if (k == 126)
		env->origin.im -= env->pixel_len * 100;
	else
		return (0);
	draw_fractal(env);
	return (0);
}

int			mouse_press_hook(int b, int x, int y, t_env *env)
{
	double	scale;

	scale = 1.5;
	if (b == 4)
	{
		env->origin.re -= env->pixel_len * x * (scale - 1);
		env->origin.im -= env->pixel_len * y * (scale - 1);
		env->pixel_len *= scale;
	}
	else if (b == 5)
	{
		env->origin.re -= env->pixel_len * x * (1 / scale - 1);
		env->origin.im -= env->pixel_len * y * (1 / scale - 1);
		env->pixel_len *= 1 / scale;
	}
	else
		return (0);
	draw_fractal(env);
	return (0);
}

static void	init_env(t_env *env)
{
	env->mlx = NULL;
	env->win = NULL;
	env->img = NULL;
	env->func.opers = oper_arr_new();
	env->start.opers = oper_arr_new();
	env->ineq_l.opers = oper_arr_new();
	env->ineq_r.opers = oper_arr_new();
	env->func.size = 0;
	env->start.size = 0;
	env->ineq_l.size = 0;
	env->ineq_r.size = 0;
	env->cx = WIN_LEN / 2;
	env->cy = WIN_WID / 2;
	env->color_rot = 0;
	env->pixel_len = 4.0 / (WIN_LEN - 1);
	env->origin = c_make(-(WIN_LEN - 1) / 2.0 * env->pixel_len,
			-(WIN_WID - 1) / 2.0 * env->pixel_len);
	env->num_threads = 16;
	env->threads = (pthread_t*)malloc(sizeof(*env->threads) * env->num_threads);
}

static void	parse_input(t_env *env, char **argv)
{
	int		i;

	i = -1;
	while (argv[3][++i])
	{
		if (argv[3][i] != '<' && argv[3][i] != '>')
			continue ;
		if (argv[3][i] == '<')
			env->comp = 0;
		else
			env->comp = 1;
		if (argv[3][i + 1] == '=')
			env->comp += 2;
		break ;
	}
	if (!argv[3][i])
		exit_prog(env, "Error: Invalid bound\n");
	parse_expr(clean_expr(ft_strdup(argv[1])), &env->func);
	parse_expr(clean_expr(ft_strdup(argv[2])), &env->start);
	parse_expr(clean_expr(ft_strsub(argv[3], 0, i)), &env->ineq_l);
	parse_expr(clean_expr(ft_strsub(argv[3], i + 1 + env->comp / 2,
					ft_strlen(argv[3]) - i - 1 - env->comp / 2)), &env->ineq_r);
	env->iter = ft_atoi(argv[4]);
	env->func.vals = (t_complex**)malloc(sizeof(*env->func.vals) * env->num_threads);
	env->start.vals = (t_complex**)malloc(sizeof(*env->start.vals) * env->num_threads);
	env->ineq_l.vals = (t_complex**)malloc(sizeof(*env->ineq_l.vals) * env->num_threads);
	env->ineq_r.vals = (t_complex**)malloc(sizeof(*env->ineq_r.vals) * env->num_threads);
	i = -1;
	while (++i < env->num_threads)
	{
		env->func.vals[i] = (t_complex*)malloc(sizeof(**env->func.vals) * env->func.size);
		env->start.vals[i] = (t_complex*)malloc(sizeof(**env->start.vals) * env->start.size);
		env->ineq_l.vals[i] = (t_complex*)malloc(sizeof(**env->ineq_l.vals) * env->ineq_l.size);
		env->ineq_r.vals[i] = (t_complex*)malloc(sizeof(**env->ineq_r.vals) * env->ineq_r.size);
	}
}

int			main(int argc, char **argv)
{
	t_env	env;

	init_env(&env);
	if (argc != 5)
		exit_prog(&env, "Usage: ./fractol function starting_value bound num_iterations\n");
	if (!(env.mlx = mlx_init()))
		exit_prog(&env, "Error: mlx_init() returned NULL\n");
	if (!(env.win = mlx_new_window(env.mlx, WIN_LEN, WIN_WID, "Fract'ol")))
		exit_prog(&env, "Error: mlx_new_window() returned NULL\n");
	if (!(env.img = mlx_new_image(env.mlx, WIN_LEN, WIN_WID)))
		exit_prog(&env, "Error: mlx_new_image() returned NULL\n");
	env.data = mlx_get_data_addr(env.img, &env.bpp, &env.sl, &env.endian);
	env.bpp /= 8;
	parse_input(&env, argv);
	draw_fractal(&env);
	mlx_key_hook(env.win, &key_release_hook, &env);
	mlx_mouse_hook(env.win, &mouse_press_hook, &env);
	mlx_hook(env.win, 6, 0, &motion_hook, &env);
	mlx_loop(env.mlx);
	return (0);
}
