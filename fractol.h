/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/01 23:20:21 by jshi              #+#    #+#             */
/*   Updated: 2016/12/21 21:36:36 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# define WIN_LEN 961
# define WIN_WID 961

# include <unistd.h>
# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include "mlx.h"
# include "libft.h"
# include "ft_printf.h"

typedef struct	s_complex
{
	double	re;
	double	im;
}				t_complex;

typedef struct	s_triple
{
	t_complex	z;
	t_complex	p;
	t_complex	c;
}				t_triple;

typedef struct	s_oper
{
	int			type;
	int			ind1;
	int			ind2;
	t_complex	val;
	t_complex	(*func1)(t_complex);
	t_complex	(*func2)(t_complex, t_complex);
}				t_oper;

typedef struct	s_expr
{
	t_oper		*opers;
	t_complex	**vals;
	int			size;
}				t_expr;

typedef struct	s_env
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*data;
	int			bpp;
	int			sl;
	int			endian;
	t_expr		func;
	t_expr		start;
	t_expr		ineq_l;
	t_expr		ineq_r;
	int			comp;
	int			iter;
	t_complex	c;
	int			cx;
	int			cy;
	int			color_rot;
	double		pixel_len;
	t_complex	origin;
	int			num_threads;
	pthread_t	*threads;
	int			move;
	double		prec;
	int			*colors;
}				t_env;

typedef struct	s_tdata
{
	t_env		*env;
	int			ind;
}				t_tdata;

t_complex		c_add(t_complex a, t_complex b);
t_complex		c_sub(t_complex a, t_complex b);
t_complex		c_mult(t_complex a, t_complex b);
t_complex		c_div(t_complex a, t_complex b);
double			mag(t_complex a);
t_complex		c_mag(t_complex a);
t_complex		c_pow(t_complex a, t_complex b);
t_complex		c_sqrt(t_complex a);
t_complex		c_ln(t_complex a);
t_complex		c_cpy(t_complex a);
t_complex		c_exp(t_complex a);
t_complex		c_sin(t_complex a);
t_complex		c_cos(t_complex a);
t_complex		c_tan(t_complex a);
t_complex		c_csc(t_complex a);
t_complex		c_sec(t_complex a);
t_complex		c_cot(t_complex a);
t_complex		c_sinh(t_complex a);
t_complex		c_cosh(t_complex a);
t_complex		c_tanh(t_complex a);
t_complex		c_csch(t_complex a);
t_complex		c_sech(t_complex a);
t_complex		c_coth(t_complex a);
t_complex		c_re(t_complex a);
t_complex		c_im(t_complex a);
void			exit_prog(t_env *env, char *msg);
t_oper			*oper_arr_new(void);
void			oper_arr_add(t_oper **arr, int *size);
int				parse_expr(char *str, t_expr *expr);
void			parse_expr2(char *str, t_expr *expr, int ind, int i);
void			parse_expr1(char *str, t_expr *expr, int ind, int i);
void			parse_expr0(char *str, t_expr *expr, int ind, int i);
char			*clean_expr(char *str);
t_complex		eval_expr(t_expr *expr, t_triple vars, int ind);
void			draw_point(t_env *env, int x, int y, int color);
void			draw_fractal(t_env *env);
int				mouse_press_hook(int b, int x, int y, t_env *env);
int				mouse_release_hook(int b, int x, int y, t_env *env);
int				motion_hook(int x, int y, t_env *env);
int				expose_hook(t_env *env);
int				key_release_hook(int k, t_env *env);
void			disp_usage(t_env *env);
void			disp_controls(void);
#endif
