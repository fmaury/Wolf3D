/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keyboard.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/10/02 12:12:51 by fmaury            #+#    #+#             */
/*   Updated: 2018/10/03 17:37:49 by fmaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	left(int keycode, t_wolf *env)
{
	t_player	*player;
	double		olddirx;
	double		oldplanex;

	player = env->player;
	olddirx = player->dirx;
	oldplanex = player->planex;
	if (keycode == 123 || keycode == 0)
	{
		fill(env);
		player->dirx = player->dirx * cos(player->rotspeed) - player->diry
		* sin(player->rotspeed);
		player->diry = olddirx * sin(player->rotspeed) + player->diry
		* cos(player->rotspeed);
		player->planex = player->planex * cos(player->rotspeed) - player->planey
		* sin(player->rotspeed);
		player->planey = oldplanex * sin(player->rotspeed) + player->planey
		* cos(player->rotspeed);
		multi_thread(env);
	}
}

void	right(int keycode, t_wolf *env)
{
	t_player	*player;
	double		olddirx;
	double		oldplanex;

	player = env->player;
	olddirx = player->dirx;
	oldplanex = player->planex;
	if (keycode == 124 || keycode == 2)
	{
		fill(env);
		player->dirx = player->dirx * cos(-player->rotspeed) - player->diry
		* sin(-player->rotspeed);
		player->diry = olddirx * sin(-player->rotspeed) + player->diry
		* cos(-player->rotspeed);
		player->planex = player->planex * cos(-player->rotspeed) -
		player->planey * sin(-player->rotspeed);
		player->planey = oldplanex * sin(-player->rotspeed) + player->planey
		* cos(-player->rotspeed);
		multi_thread(env);
	}
}

int		iswall(int up_down, t_wolf *env, double x, double y)
{
	int			i;
	t_player	*player;

	i = 0;
	player = env->player;
	while (i < 3)
	{
		if (env->map->map[(int)x][(int)y] != '1')
		{
			if (up_down == 0)
			{
				x += player->dirx * player->movespeed;
				y += player->diry * player->movespeed;
			}
			else
			{
				x -= player->dirx * player->movespeed;
				y -= player->diry * player->movespeed;
			}
			i++;
		}
		else
			return (0);
	}
	return (1);
}

void	up_down(int keycode, t_wolf *env)
{
	t_player	*player;

	player = env->player;
	if (keycode == 126 || keycode == 13)
	{
		if (iswall(0, env, player->x + player->dirx * player->movespeed,\
		player->y + player->diry * player->movespeed))
		{
			fill(env);
			player->x += player->dirx * player->movespeed;
			player->y += player->diry * player->movespeed;
			multi_thread(env);
		}
	}
	if (keycode == 125 || keycode == 1)
	{
		if (iswall(1, env, player->x - player->dirx * player->movespeed,\
		player->y - player->diry * player->movespeed))
		{
			fill(env);
			player->x -= player->dirx * player->movespeed;
			player->y -= player->diry * player->movespeed;
			multi_thread(env);
		}
	}
}

int		keyboard(int keycode, t_wolf *env)
{
	left(keycode, env);
	right(keycode, env);
	up_down(keycode, env);
	if (keycode == 46)
	{
		if (env->sound)
		{
			system("pkill afplay");
			env->sound = 0;
		}
		else
		{
			system("killall afplay 2&>/dev/null >/dev/null\n afplay \
				./sound/sound.mp3&");
			env->sound = 1;
		}
	}
	if (keycode == 53)
	{
		system("pkill afplay");
		free_struct(env);
		exit(0);
	}
	return (0);
}
