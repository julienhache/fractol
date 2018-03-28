/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_fract.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/26 18:05:52 by jhache            #+#    #+#             */
/*   Updated: 2018/03/28 13:54:39 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void		init_fract(t_fractol *frctl, t_name fractale_name)
{
	t_fractal	*fract;
	int			i;
	size_t		work_size;

	work_size = X_SIZE * Y_SIZE;
	fract = &frctl->fract;
	if (fractale_name == none)
	{
		ft_deallocate(frctl, frctl->ptr);
		exit(-1);
	}
	frctl->fract.name = fractale_name;
	i = 0;
	while (fract->name != g_fract[i].name)
		++i;
	fract->max_iter = MAX_ITER;
	g_fract[i].init_ptr(fract);
	g_fract[i].fun_ptr(frctl, &work_size);
	printf("x1 = %f\nx2 = %f\ny1 = %f\ny2 = %f\n", fract->x1, fract->x2, fract->y1, fract->y2);
	printf("MADELBROTX1 = %f\nMADELBROTX2 = %f\nMADELBROTY1 = %f\nMADELBROTY2 = %f\n", MANDELBROTX1, MANDELBROTX2, MANDELBROTY1, MANDELBROTY2);//FONCTION INTERDITE
	printf("Max_iter = %d\n", fract->max_iter);
}

void		init_julia(t_fractal *fract)
{
	exit(666);
}

void		init_mandelbrot(t_fractal *fract)
{
	float	x_range;
	float	y_range;
	float	tmp;

	x_range = MANDELBROTX2 - MANDELBROTX1;
	y_range = MANDELBROTY2 - MANDELBROTY1;
	if ((X_SIZE / x_range) > (Y_SIZE / y_range))
	{
		tmp = (Y_SIZE * x_range / y_range);
		fract->y1 = MANDELBROTY1;
		fract->y2 = MANDELBROTY2;
		fract->x1 = MANDELBROTX1 - (((X_SIZE - tmp) / (tmp / x_range)) / 2);
		fract->x2 = MANDELBROTX2 + (((X_SIZE - tmp) / (tmp / x_range)) / 2);
	}
	else
	{
		tmp = (X_SIZE * y_range / x_range);
		fract->y1 = MANDELBROTY1 - (((Y_SIZE - tmp) / (tmp / y_range)) / 2);
		fract->y2 = MANDELBROTY2 + (((Y_SIZE - tmp) / (tmp / y_range)) / 2);
		fract->x1 = MANDELBROTX1;
		fract->x2 = MANDELBROTX2;
	}
}