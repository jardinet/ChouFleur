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
#include <stdio.h> //TOREMOVe

# include "./libft/libft.h"
# include "./minilibx/mlx.h"
# include <math.h>

# define SPACE ' '
# define OK 0
# define NOT_OK 1


# define ESC 53
# define PLUS 69
# define MINUS 78

# define LEFT 123
# define RIGHT 124
# define UP 126
# define BOTTOM 125
# define KSPACE 49


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

typedef struct s_scale
{
	float		xmin;
	float		xmax;
	float		ymin;
	float		ymax;
	float		zoom_x;
	float		zoom_y;
	float		mx;
	float		my;
	float		iter_max;
}				t_scale;


/**
* c for constant
* i for imaginary
* r for real
* z for complex
**/

typedef struct s_mbrot
{
	float			cr;
	float			ci;
	float			zr;
	float			zi;
}				t_mbrot;

typedef struct	s_win
{
	void	*id;
	int		fractal; // JULIA/MANDEL/SHIP
	void	*win_ptr;
	void	*mlx_img;
	char	*buff;

	t_scale s;
	t_mbrot f;
	int		bpp;
	int		sizeline;
	int		endian;
}				t_win;

void			init_window(t_win *w);
void			affichage(t_win *w);
void 			fractal(t_win *w);
void			fill_img_buffer(t_win *w, int x, int y, int color);

#endif
