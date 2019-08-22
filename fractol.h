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

# define SPACE ' '
# define OK 0
# define NOT_OK 1


# define WINX 512
# define WINY 512

# define JULIA 1
# define MANDEL 2
# define BOAT 3


typedef struct s_scale
{
	float		xmin;
	float		xmax;
	float		ymin;
	float		ymax;
	float		zoom_x;
	float		zoom_y;
	float		iter_max;
}				t_scale;

// typedef struct s_julia
// {
// 	int			zr;
// 	int			zi;
// 	int			iter;
// }				t_julia;

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
	// int			iter;
}				t_mbrot;

typedef struct	s_win
{
	void	*id;
	int		fractal; // JULIA/MANDEL/BOAT
	void	*win_ptr;
	void	*mlx_img;
	char	*buff;

	int		bpp;
	int		sizeline;
	int		endian;
}				t_win;

void			initialisation_window(t_win *w);
void			affichage(t_win *w);
void 			fractal(t_win *w);
void			fill_img_buffer(t_win *w, int x, int y);

#endif
