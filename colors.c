/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwragg <mwragg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/23 01:42:36 by mwragg            #+#    #+#             */
/*   Updated: 2019/08/23 01:42:37 by mwragg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int		rainbow_color(int i, t_win *w)
{
	double	c;
	int		red;
	int		green;
	int		blue;

	if (i == w->s.iter_max)
		return (0);
	c = (i + 1);
	red = cos(c + 1) * 127 + 128;
	green = cos(c + 2) * 127 + 128;
	blue = cos(c + 4) * 127 + 128;
	return ((red << 16) + (blue << 8) + green);
}

void	set_color(t_win *w, int i, int x, int y)
{
	int color;

	if (w->color_state == 1)
	{
		color = 0;
		if (i == w->s.iter_max)
			fill_img_buffer(w, x, y, color);
		else
		{
			color = ((0 << 16) + (0 << 8) + (i * 255 / w->s.iter_max));
			fill_img_buffer(w, x, y, color);
		}
	}
	else
		fill_img_buffer(w, x, y, rainbow_color(i, w));
}
