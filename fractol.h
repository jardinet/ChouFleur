/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mwragg <mwragg@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/11 23:08:40 by mwragg            #+#    #+#             */
/*   Updated: 2019/07/11 23:11:23 by mwragg           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H

# include "./libft/libft.h"
# include "./minilibx/mlx.h"
# include <math.h>

# define ESC 53
# define PLUS 69
# define MINUS 78

# define LEFT 123
# define RIGHT 124
# define UP 126
# define BOTTOM 125
# define SPACE 49
# define C 8
# define S 1

# define WINX 1000
# define WINY 1000

# define JULIA 1
# define MANDEL 2
# define SHIP 3

# define MOTION_NOTIFY			6
# define PTR_MOTION_MASK		(1L << 6)

# define LEFT_CLIC	1
# define RIGHT_CLIC	2
# define SCROLL_DW	4
# define SCROLL_UP	5

typedef struct		s_scale
{
	double			xmin;
	double			xmax;
	double			ymin;
	double			ymax;
	double			zoom_x;
	double			zoom_y;
	double			mx;
	double			my;
	int				iter_max;
}					t_scale;

typedef struct		s_mbrot
{
	double			cr;
	double			ci;
	double			zr;
	double			zi;
}					t_mbrot;

typedef struct		s_win
{
	void			*id;
	int				fractal;
	int				color_state;
	int				stop;
	void			*win_ptr;
	void			*mlx_img;
	char			*buff;
	t_scale			s;
	t_mbrot			f;
	int				bpp;
	int				sizeline;
	int				endian;
}					t_win;

void				init_window(t_win *w);
void				affichage(t_win *w);
void				fractal(t_win *w);
void				fill_img_buffer(t_win *w, int x, int y, int color);
t_scale				init_scale(void);
int					reset(t_win *w);

int					key_events(int key, t_win *w);
int					move_julia(int x, int y, t_win *w);
int					mouse_hook(int key, int x, int y, t_win *w);

void				set_color(t_win *w, int i, int x, int y);

#endif
