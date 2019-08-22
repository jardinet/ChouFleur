/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   management_mlx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwragg <mwragg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 23:06:22 by mwragg            #+#    #+#             */
/*   Updated: 2019/07/12 00:04:26 by mwragg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

static int		reset(t_win *w)
{
	ft_bzero(w->buff, w->sizeline * WINY);
	fractal(w);
	mlx_put_image_to_window(w->id, w->win_ptr,
			w->mlx_img, 0, 0);
	return (0);
}


int		key_events(int key, t_win *w)
{
	float k;

	k = 0.2 * (w->s.xmax - w->s.xmin);
	if (key == ESC)
		exit(0);
	if (key == KSPACE)
		w->fractal = w->fractal == 3 ? 1 : w->fractal + 1;
	if (key == PLUS && w->s.iter_max < 500)
		w->s.iter_max *=2;
	if (key == MINUS && w->s.iter_max > 4)
		w->s.iter_max /= 2;
	if (key == RIGHT){
		w->s.xmin += k;
		w->s.xmax += k;
	}
		if (key == LEFT){
		w->s.xmin -= k;
		w->s.xmax -= k;
	}
	if (key == BOTTOM){
		w->s.ymin += k;
		w->s.ymax += k;
	}
	if (key == UP){
		w->s.ymin -= k;
		w->s.ymax -= k;
	}

	return (reset(w));
}

int		red_cross(void)
{
	exit(0);
}



int						motion_hook(int x, int y, t_win *w)
{
	if (x >= 0 && y >= 0 && x <= WINX && y <= WINY && w->fractal == JULIA)
	{
		w->f.cr = x / w->s.zoom_x + w->s.xmin;
		w->f.ci = y / w->s.zoom_y + w->s.ymin;
	}
	else
	 return (0);
	return (reset(w));
}

t_scale		reset_scale(t_scale s, float cr, float ci)
{
	float dcr;
	float dci;

	dcr = cr / 2;
	dci = ci / 2;

	s.xmin = s.mx - dcr;
	s.xmax = s.mx + dcr;
	s.ymin = s.my - dci;
	s.ymax = s.my + dci;
	s.zoom_x = (float)WINX / (s.xmax - s.xmin);
    s.zoom_y = (float)WINY / (s.ymax - s.ymin);
	return s;	
}
int				mouse_hook(int key, int x, int y, t_win *w)
{
	t_scale s;
	float cr;
	float ci;
	
	s = w->s;
	cr = s.xmax - s.xmin;
	ci = s.ymax - s.ymin;
	s.mx = (float)(cr / WINX) * x + s.xmin;
	s.my = (float)(ci / WINY) * y + s.ymin;
	if ((key == LEFT_CLIC || key == SCROLL_UP) && x <= WINX && y <= WINY)
	{
		cr *= 0.8;
		ci *= 0.8;
	}
	else if ((key == RIGHT_CLIC || key == SCROLL_DW) && x <= WINX && y <= WINY)
	{
		cr /= 0.8;
		ci /= 0.8;
	}
	w->s = reset_scale(s, cr, ci);
	return (reset(w));
}

void			affichage(t_win *w)
{
	ft_putendl("Affichage called");
	mlx_put_image_to_window(w->id, w->win_ptr, w->mlx_img, 0, 0);
	mlx_hook(w->win_ptr, 17, (1L << 17), &red_cross, 0);
	mlx_key_hook(w->win_ptr, key_events, w);
	mlx_mouse_hook(w->win_ptr, mouse_hook, w);
	mlx_hook(w->win_ptr, MOTION_NOTIFY, PTR_MOTION_MASK,
				motion_hook, w);
	mlx_loop(w->id);
}


void	init_window(t_win *w)
{
	w->id = mlx_init();
	w->win_ptr = mlx_new_window(w->id, WINX, WINY, "The Winx adventures");
	w->mlx_img = mlx_new_image(w->id, WINX, WINY);
	w->buff = mlx_get_data_addr(w->mlx_img, &w->bpp, &w->sizeline, &w->endian);
}
