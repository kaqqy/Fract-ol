/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 23:19:35 by jshi              #+#    #+#             */
/*   Updated: 2016/12/21 20:21:20 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

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
	env->color_rot = 0;
	env->pixel_len = 4.0 / (WIN_LEN - 1);
	env->origin = (t_complex){-(WIN_LEN - 1) / 2.0 * env->pixel_len,
			-(WIN_WID - 1) / 2.0 * env->pixel_len};
	env->num_threads = 16;
	env->threads = (pthread_t*)malloc(sizeof(*env->threads) * env->num_threads);
	env->move = -1;
	env->c = (t_complex){env->origin.re + (WIN_LEN / 2) * env->pixel_len,
			env->origin.im + (WIN_WID / 2) * env->pixel_len};
	env->prec = 0.0;
}

static void	parse_input2(t_env *env)
{
	int		i;

	env->func.vals = (t_complex**)malloc(sizeof(*env->func.vals)
			* env->num_threads);
	env->start.vals = (t_complex**)malloc(sizeof(*env->start.vals)
			* env->num_threads);
	env->ineq_l.vals = (t_complex**)malloc(sizeof(*env->ineq_l.vals)
			* env->num_threads);
	env->ineq_r.vals = (t_complex**)malloc(sizeof(*env->ineq_r.vals)
			* env->num_threads);
	i = -1;
	while (++i < env->num_threads)
	{
		env->func.vals[i] = (t_complex*)malloc(sizeof(**env->func.vals)
				* env->func.size);
		env->start.vals[i] = (t_complex*)malloc(sizeof(**env->start.vals)
				* env->start.size);
		env->ineq_l.vals[i] = (t_complex*)malloc(sizeof(**env->ineq_l.vals)
				* env->ineq_l.size);
		env->ineq_r.vals[i] = (t_complex*)malloc(sizeof(**env->ineq_r.vals)
				* env->ineq_r.size);
	}
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
	env->iter = (env->iter < 1) ? 1 : env->iter;
	parse_input2(env);
}

static void	disp_usage(t_env *env)
{
	ft_printf("Usage: ./fractol function starting_value bound iterations\n");
	exit_prog(env, "");
}

int			main(int argc, char **argv)
{
	t_env	env;

	init_env(&env);
	if (argc != 5)
		disp_usage(&env);
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
	mlx_hook(env.win, 5, 0, &mouse_release_hook, &env);
	mlx_hook(env.win, 6, 0, &motion_hook, &env);
	mlx_loop(env.mlx);
	return (0);
}
