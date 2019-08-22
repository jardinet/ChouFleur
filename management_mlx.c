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

int		key_events(int key, t_win *w)
{
	(void)w;
	if (key == 53)
		exit(0);
	return (0);
}

int		red_cross(void)
{
	exit(0);
}


static int		reset(t_win *w)
{
	ft_bzero(w->buff, w->sizeline * WINY);
	fractal(w);
	mlx_put_image_to_window(w->id, w->win_ptr,
			w->mlx_img, 0, 0);
	return (0);
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

int				mouse_hook(int button, int x, int y, t_win *w)
{
if ((button == LEFT_CLIC || button == SCROLL_UP) && x <= WINX && y <= WINY)
	{
		w->s.xmin *= 1.5;
		w->s.xmin *= 1.5;

	}
	else if ((button == RIGHT_CLIC || button == SCROLL_DW) && x <= WINX && y <= WINY)
	{
		w->s.xmin /= 1.5;
		w->s.xmin /= 1.5;

	}
	(void)w;
return (reset(w));
}

void			affichage(t_win *w)
{
	ft_putendl("Affichage called");
	mlx_put_image_to_window(w->id, w->win_ptr, w->mlx_img, 0, 0);
	mlx_hook(w->win_ptr, 17, (1L << 17), &red_cross, 0);
	mlx_key_hook(w->win_ptr, key_events, &w);
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
