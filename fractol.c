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

void	fill_img_buffer(t_win *w, int x, int y)
{
	int position;
	char color = (char)255;

	if (0 <= x && x < WINX && 0 <= y && y < WINY)
	{
		position = y * w->sizeline + (x * 4);
		w->buff[position] = color;
		w->buff[position + 1] = color;
		w->buff[position + 2] = color;
	}
}

int		choose_fractal(char *s, t_win *w)
{
	if (!ft_strcmp(s, "mandelbrot"))
	return (w->fractal = MANDEL);
	else if (!ft_strcmp(s, "julia"))
	return (w->fractal = JULIA);
	else if (!ft_strcmp(s, "boat"))
	return (w->fractal = BOAT);
	else 
	return 0;

}

int		main(int ac, char **argv)
{
	t_win win;

	(void) argv;
	if (ac == 2 && choose_fractal(argv[1], &win)) 
	{
		initialisation_window(&win);
		fractal(&win);
		affichage(&win);
	}
	else
		 ft_strexit("usage : please specify julia, mandelbrot or A COMPLETER");
	return (0);
}
