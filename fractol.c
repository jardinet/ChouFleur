/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwragg <mwragg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 23:16:39 by mwragg            #+#    #+#             */
/*   Updated: 2019/08/23 01:45:31 by mwragg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void	fill_img_buffer(t_win *w, int x, int y, int color)
{
	int	position;
	int	*ptr;

	if (0 <= x && x < WINX && 0 <= y && y < WINY)
	{
		position = y * WINX * 4 + x * 4;
		ptr = (int *)(void*)&w->buff[position];
		*ptr = color;
	}
}

int		choose_fractal(char *s, t_win *w)
{
	if (!ft_strcmp(s, "mandelbrot"))
		return (w->fractal = MANDEL);
	else if (!ft_strcmp(s, "julia"))
		return (w->fractal = JULIA);
	else if (!ft_strcmp(s, "ship"))
		return (w->fractal = SHIP);
	else if (!ft_strcmp(s, "usage"))
	{
		ft_putendl("Space to change fractal, (+/-) to change iterations.");
		ft_putendl("Arrow keys to move around.");
		ft_putendl("Left clic to recenter, right clic for fast dezoom.");
		ft_putendl("Scroll for zoom, and C to switch color mode.");
		ft_strexit("S to (de)activate mouse movement on julia.");
	}
	return (0);
}

t_scale	init_scale(void)
{
	t_scale s;

	s.xmin = -2.1;
	s.xmax = 0.6;
	s.ymin = -1.2;
	s.ymax = 1.2;
	s.iter_max = 16;
	s.mx = 0;
	s.zoom_x = (double)WINX / (s.xmax - s.xmin);
	s.zoom_y = (double)WINY / (s.ymax - s.ymin);
	return (s);
}

int		main(int ac, char **argv)
{
	t_win win;

	if (ac == 2 && choose_fractal(argv[1], &win))
	{
		win.f.cr = 0.285;
		win.f.ci = 0.01;
		win.color_state = 1;
		win.stop = 0;
		init_window(&win);
		win.s = init_scale();
		fractal(&win);
		affichage(&win);
	}
	else
	{
		ft_putendl("Usage: Please specify either mandelbrot, julia or ship !");
		ft_strexit("For help, type usage.");
	}
	return (0);
}
