/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractales.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwragg <mwragg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/12 00:03:13 by mwragg            #+#    #+#             */
/*   Updated: 2019/07/12 00:03:27 by mwragg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fractol.h"

int mandel(t_scale *s, int x, int y)
{
    t_mbrot f;
    float tmp;
    int i;

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

int boat(t_scale *s, int x, int y)
{
    t_mbrot f;
    float tmp;
    int i;

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

int julia(t_scale *s, t_win *w, int x, int y)
{
    t_mbrot f;
    float tmp;
    int i;

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

int		glow(int c1, int c2, float perc)
{
	return (((int)((c1 & 0xFF) * perc + (c2 & 0xFF) * (1 - perc)) & 0xFF)
		| ((int)((c1 & 0xFF00) * perc + (c2 & 0xFF00) * (1 - perc)) & 0xFF00)
		| ((int)((c1 & 0xFF0000) * perc + (c2 & 0xFF0000) * (1 - perc))
			& 0xFF0000)
		| ((int)((c1 & 0xFF000000) * perc + (c2 & 0xFF000000) * (1 - perc))
			& 0xFF000000));
}

int						rainbow_color(int i, t_win *w)
{
	register double		c;
	register int		red;
	register int		green;
	register int		blue;
    
	if (i == w->s.iter_max)
		return (0);
	c = (i + 1);
    
	red = cos(c) * 127 + 128;
	green = cos(c + 2) * 127 + 128;
	blue = cos(c + 2 + 2) * 127 + 128;
	return ((red << 16) + (blue << 8) + green);
}

void fractal(t_win *w) 
{
    int x;
    int y;
    int color;
    int i;

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
                i = boat(&w->s, x, y);

            // color = rainbow_color(i, w);
            color = 0;

        if (i == w->s.iter_max)
            fill_img_buffer(w, x, y, color);
        else
            {
                color = ((0 << 16) + (0 << 8) + (i * 255/ w->s.iter_max));
                fill_img_buffer(w, x, y, color);
            }
        }
    }
}



// void boat(void)
// {}