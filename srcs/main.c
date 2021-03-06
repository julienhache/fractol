/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jhache <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/01 13:07:24 by jhache            #+#    #+#             */
/*   Updated: 2018/04/10 17:53:08 by jhache           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define FRACTOL_MAIN
#include "fractol.h"

t_frct_lst		g_fract[] = {
	{mandelbrot, &init_mandelbrot, &ocl_mandelbrot},
	{julia, &init_julia, &ocl_julia},
	{burning_ship, &init_burning_ship, &ocl_burning_ship},
	{multibrot, &init_mandelbrot, &ocl_multibrot}};

t_frct_clr_type	g_clr_type[] = {
	{gradient, &color_gradient},
	{reverse_gradient, &color_reverse_gradient},
	{modulo_steps, &color_steps},
	{randomator2000, &color_random}};
#undef FRACTOL_MAIN

void			ft_usage(void)
{
	ft_printf("usage: ./fractol \"fractal_name\"\n");
	ft_printf("-> mandelbrot\n-> julia\n-> burning_ship\n-> multibrot\n");
	exit(0);
}

static void		ft_error(const char *perror_msg)
{
	perror(perror_msg);
	ft_putchar('\n');
	exit(-1);
}

void			init_hook(t_fractol *frctl)
{
	mlx_hook(frctl->mlx->win, KEYPRESS, KEYPRESSMASK, &key_hook, (void *)frctl);
	mlx_hook(frctl->mlx->win, MOTIONNOTIFY, POINTERMOTIONMASK,
		&ft_get_cursor_pos, (void *)frctl);
	mlx_hook(frctl->mlx->win, BUTTONPRESS, BUTTONPRESSMASK,
		&ft_mouse_event, (void *)frctl);
}

int				main(int ac, char **av)
{
	t_fractol	*frctl;
	void		*anti_leaks_ptr;
	t_name		fractale_name;

	if (ac != 2 || (fractale_name = ft_select_fract(av[1])) == none)
		ft_usage();
	if (!(frctl = (t_fractol *)ft_memalloc(sizeof(t_fractol))))
		ft_error("malloc");
	frctl->ptr = &anti_leaks_ptr;
	if (!(frctl->mlx = ft_init_mlx(&anti_leaks_ptr))
		|| !(frctl->ocl = ft_init_opencl())
		|| init_iter_array(frctl) != 0)
		return (-1);
	frctl->fract.clr.color = 0xFFFFFF;
	init_fract(frctl, fractale_name);
	frctl->clrpick = ft_colorpicker(frctl->mlx->mlxptr,
			&get_color, (void *)frctl, "Color_picker");
	mlx_put_image_to_window(frctl->mlx->mlxptr,
		frctl->mlx->win, frctl->mlx->img->ptr, 0, 0);
	init_hook(frctl);
	mlx_loop(frctl->mlx->mlxptr);
	return (0);
}
