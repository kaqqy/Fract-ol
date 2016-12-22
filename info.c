/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   info.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jshi <marvin@42.fr>                        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/21 21:21:41 by jshi              #+#    #+#             */
/*   Updated: 2016/12/22 00:26:46 by jshi             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	disp_usage(t_env *env)
{
	ft_printf("Usage: ./fractol function starting_value bound iterations\n\n");
	ft_printf("Ex:\nMandelbrot: ./fractol \"z*z+p\" 0 \"|z|<=2\" 50\n");
	ft_printf("Julia: ./fractol \"z*z+c\" p \"|z|<=2\" 50\n\n");
	ft_printf("The function is the value of f(z) used for iterating\n");
	ft_printf("The starting value is the value that z starts as\n");
	ft_printf("The bound is an inequality for when the point is still \
in the set\n");
	ft_printf("The iterations is the maximum number of times the iterated\n\n");
	ft_printf("The valid variables are\n");
	ft_printf("z: The input for the function\n");
	ft_printf("p: The location of the pixel being drawn\n");
	ft_printf("c: The location of the cursor\n\n");
	ft_printf("The following operations are supported:\n");
	ft_printf("+ - * / ^ ||\n");
	ft_printf("sqrt ln exp re im\n");
	ft_printf("sin cos tan csc sec cot\n");
	ft_printf("sinh cosh tanh csch sech coth\n");
	exit_prog(env, "");
}

void	disp_controls(void)
{
	ft_printf("Controls:\n");
	ft_printf("Arrow keys : Translate the fractal\n");
	ft_printf("< > : Rotate the color palette\n");
	ft_printf("+ - : Increase/decrease the number of iterations\n");
	ft_printf("[ ] : Increase/decrease the precision of the fractal \
and decrease/increase the speed of drawing the fractal\n");
	ft_printf("Click/drag to set/change the location of the cursor\n");
	ft_printf("Scroll to zoom in/out\n");
}
