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

int		reset(t_win *w)
{
	ft_bzero(w->buff, w->sizeline * WINY);
	fractal(w);
	mlx_put_image_to_window(w->id, w->win_ptr,
			w->mlx_img, 0, 0);
	return (0);
}

void	affichage(t_win *w)
{
	mlx_put_image_to_window(w->id, w->win_ptr, w->mlx_img, 0, 0);
	mlx_key_hook(w->win_ptr, key_events, w);
	mlx_mouse_hook(w->win_ptr, mouse_hook, w);
	mlx_hook(w->win_ptr, MOTION_NOTIFY, PTR_MOTION_MASK, move_julia, w);
	mlx_loop(w->id);
}

void	init_window(t_win *w)
{
	w->id = mlx_init();
	w->win_ptr = mlx_new_window(w->id, WINX, WINY, "The Winx adventures");
	w->mlx_img = mlx_new_image(w->id, WINX, WINY);
	w->buff = mlx_get_data_addr(w->mlx_img, &w->bpp, &w->sizeline, &w->endian);
}
