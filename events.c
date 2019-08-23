/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwragg <mwragg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 00:49:24 by mwragg            #+#    #+#             */
/*   Updated: 2019/08/23 01:33:19 by mwragg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int			move_julia(int x, int y, t_win *w)
{
	if (w->stop)
		return (0);
	if (x >= 0 && y >= 0 && x <= WINX && y <= WINY && w->fractal == JULIA)
	{
		w->f.cr = x / w->s.zoom_x + w->s.xmin;
		w->f.ci = y / w->s.zoom_y + w->s.ymin;
	}
	else
		return (0);
	return (reset(w));
}

t_scale		reset_scale(t_scale s, double dx, double dy)
{
	double	midx;
	double	midy;

	midx = dx / 2;
	midy = dy / 2;
	s.xmin = s.mx - midx;
	s.xmax = s.mx + midx;
	s.ymin = s.my - midy;
	s.ymax = s.my + midy;
	s.zoom_x = (double)WINX / dx;
	s.zoom_y = (double)WINY / dy;
	return (s);
}

int			mouse_hook(int key, int x, int y, t_win *w)
{
	t_scale	s;
	double	dx;
	double	dy;

	s = w->s;
	dx = s.xmax - s.xmin;
	dy = s.ymax - s.ymin;
	s.mx = (double)(dx / WINX) * x + s.xmin;
	s.my = (double)(dy / WINY) * y + s.ymin;
	if ((key == SCROLL_DW) && x <= WINX && y <= WINY)
	{
		dx *= 0.8;
		dy *= 0.8;
	}
	else if ((key == RIGHT_CLIC || key == SCROLL_UP) && x <= WINX && y <= WINY)
	{
		dx /= key == RIGHT_CLIC ? 0.4 : 0.8;
		dy /= key == RIGHT_CLIC ? 0.4 : 0.8;
	}
	w->s = reset_scale(s, dx, dy);
	return (reset(w));
}

void		arrows(int key, t_win *w)
{
	double k;

	k = 0.2 * (w->s.xmax - w->s.xmin);
	if (key == RIGHT)
	{
		w->s.xmin += k;
		w->s.xmax += k;
	}
	if (key == LEFT)
	{
		w->s.xmin -= k;
		w->s.xmax -= k;
	}
	if (key == BOTTOM)
	{
		w->s.ymin += k;
		w->s.ymax += k;
	}
	if (key == UP)
	{
		w->s.ymin -= k;
		w->s.ymax -= k;
	}
}

int			key_events(int key, t_win *w)
{
	if (key == ESC)
		exit(0);
	if (key == S)
		w->stop = !w->stop;
	if (key == C)
		w->color_state = w->color_state == 1 ? 2 : 1;
	if (key == SPACE)
	{
		w->fractal = w->fractal == 3 ? 1 : w->fractal + 1;
		w->s = init_scale();
	}
	if (key == PLUS && w->s.iter_max < 500)
		w->s.iter_max *= 1.2;
	if (key == MINUS && w->s.iter_max > 5)
		w->s.iter_max /= 1.2;
	arrows(key, w);
	return (reset(w));
}
