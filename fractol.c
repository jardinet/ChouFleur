/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwragg <mwragg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 23:16:39 by mwragg            #+#    #+#             */
/*   Updated: 2019/07/11 23:54:26 by mwragg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

void			fill_img_buffer(t_win *w, int x, int y, int color)
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
	ft_strexit("Space to change fractal, (+/-) to change iterations, arrow key to move around");
	return (0);
}

t_scale init_scale(void)
{
	t_scale s;

	s.xmin = -2.1;
    s.xmax = 0.6;
    s.ymin = -1.2;
    s.ymax = 1.2;
    s.iter_max = 16;
    s.zoom_x = (float)WINX / (s.xmax - s.xmin);
    s.zoom_y = (float)WINY / (s.ymax - s.ymin);
	return s;
}

int		main(int ac, char **argv)
{
	t_win win;

	win.f.cr = 0.285;
    win.f.ci = 0.01;
	if (ac == 2 && choose_fractal(argv[1], &win)) 
	{
		init_window(&win);
		win.s = init_scale();
		fractal(&win);
		affichage(&win);
	}
	else
		 ft_strexit("Usage : Please specify either mandelbrot, julia or ship !\nFor help, type usage.");
	return (0);
}
