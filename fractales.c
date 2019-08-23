/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractales.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwragg <mwragg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 00:03:13 by mwragg            #+#    #+#             */
/*   Updated: 2019/08/23 01:42:02 by mwragg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		mandel(t_scale *s, int x, int y)
{
	t_mbrot f;
	double	tmp;
	int		i;

	f.cr = x / s->zoom_x + s->xmin;
	f.ci = y / s->zoom_y + s->ymin;
	f.zr = 0;
	f.zi = 0;
	i = 0;
	while (i < s->iter_max && (f.zr * f.zr) + (f.zi * f.zi) < 4)
	{
		tmp = f.zr;
		f.zr = (f.zr * f.zr) - (f.zi * f.zi) + f.cr;
		f.zi = 2 * f.zi * tmp + f.ci;
		i++;
	}
	return (i);
}

int		ship(t_scale *s, int x, int y)
{
	t_mbrot	f;
	double	tmp;
	int		i;

	f.cr = x / s->zoom_x + s->xmin;
	f.ci = y / s->zoom_y + s->ymin;
	f.zr = 0;
	f.zi = 0;
	i = 0;
	while (i < s->iter_max && (f.zr * f.zr) + (f.zi * f.zi) < 4)
	{
		tmp = f.zr;
		f.zr = fabs((f.zr * f.zr) - (f.zi * f.zi) + f.cr);
		f.zi = fabs(2 * f.zi * tmp + f.ci);
		i++;
	}
	return (i);
}

int		julia(t_scale *s, t_win *w, int x, int y)
{
	t_mbrot	f;
	double	tmp;
	int		i;

	f = w->f;
	f.zr = x / s->zoom_x + s->xmin;
	f.zi = y / s->zoom_y + s->ymin;
	i = 0;
	while (i < s->iter_max && (f.zr * f.zr) + (f.zi * f.zi) < 4)
	{
		tmp = f.zr;
		f.zr = (f.zr * f.zr) - (f.zi * f.zi) + f.cr;
		f.zi = 2 * f.zi * tmp + f.ci;
		i++;
	}
	return (i);
}

void	fractal(t_win *w)
{
	int	x;
	int	y;
	int	i;

	x = -1;
	while (++x < WINX)
	{
		y = -1;
		while (++y < WINY)
		{
			if (w->fractal == MANDEL)
				i = mandel(&w->s, x, y);
			else if (w->fractal == JULIA)
				i = julia(&w->s, w, x, y);
			else
				i = ship(&w->s, x, y);
			set_color(w, i, x, y);
		}
	}
}
