/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wolf.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: francoismaury <francoismaury@student.42    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/12 16:55:22 by fmaury            #+#    #+#             */
/*   Updated: 2018/08/05 01:04:14 by francoismau      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WOLF_H
# define WOLF_H

#define WIDTH 1200
#define HEIGHT 900
#define NBTHREAD 4

#include "../libft/srclib/libft.h"
#include <fcntl.h>
# include "../minilibx_macos/mlx.h"
#include <math.h>
#include <stdio.h>
# include <pthread.h>

/*
** Mlx.h pour linux
** # include "../minilibx_linux/mlx.h"
*/



typedef struct      s_map
{
    char            **map;
    int             x;
    int             y;
}                   t_map;

typedef struct		s_img
{
	void			*im;
	int			    *imc;
	int				imlen;
	int				bpp;
	int				endi;
    int             width;
    int             height;
}					t_img;

typedef struct      s_player
{
    double          x;
    double          y;
    double          planex;
    double          planey;
    int             color1;
    int             color2;
    double          dirx;
    double          diry;
    double          movespeed;
    double          rotspeed;
}                   t_player;

typedef struct      s_world
{
    double          wallx;
    int             side;
    double          sidedistx;
    double          sidedisty;
    double          deltadistx;
    double          deltadisty;
    double          perpwalldist;
    int             hwall;
    int             stepx;
    int             stepy;
    double          raydirx;
    double          raydiry;
    int             mapx;
    int             mapy;
    int             color;
    int             drawstart;
    int             drawend;
    int             texx;
    int			    *imc1;
    int			    *imc2;
    int			    *imc;
    int             texwidth;
    int             texheight;
    int             texwidth1;
    int             texheight1;
    int             texwidth2;
    int             texheight2;
}                   t_world;

typedef struct      s_wolf
{
    void            *mlx;
    void            *win;
    void			*img;
    int	            *data;
    int             fd;
    t_map           *map;
    t_player        *player;
    t_img           wall1;
    t_img           wall2;
    t_img           wall3;
    t_img           wall4;
    t_img           sky;
    t_img           floor;
}                   t_wolf;

typedef struct		s_thread
{
	t_wolf			*env;
	int				i;
}					t_thread;

int         parse(t_wolf *env, t_map * map, t_player *player);
void        wolf(t_wolf *env);
void        dda_algo(t_wolf *env, int i, int width);
void	multi_thread(t_wolf *env);

double      deg_to_rad(double deg);
double      rad_to_deg(double rad);

#endif
