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

void mandel(t_scale *s, t_win *w, int x, int y)
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
    if (i == s->iter_max)
        fill_img_buffer(w, x, y);

}

void boat(t_scale *s, t_win *w, int x, int y)
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
    if (i == s->iter_max)
        fill_img_buffer(w, x, y);


}

void julia(t_scale *s, t_win *w, int x, int y)
{
    t_mbrot f;
    float tmp;
    int i;

    f = w->f;
    // printf("%f\t%f\n", f.cr, f.ci);
    // f.cr = -0.75;
    // f.ci = 0.1;

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
    if (i == s->iter_max)
        fill_img_buffer(w, x, y);

}

void fractal(t_win *w) 
{
    int x;
    int y;


    x = -1;
    while (++x < WINX)
    {
        y = -1;
        while (++y < WINY)
        {
            if (w->fractal == MANDEL)
            mandel(&w->s, w, x, y);
            else if (w->fractal == JULIA)
            julia(&w->s, w, x, y);
            else
            boat(&w->s, w, x, y);
        }
    }
    // affichage(w);
}



// void boat(void)
// {}