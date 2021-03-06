/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multi_thread.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fmaury <fmaury@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/08/04 00:19:49 by francoismau       #+#    #+#             */
/*   Updated: 2018/10/02 10:57:57 by fmaury           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wolf.h"

void	*dda_thread(t_thread *thr)
{
	dda_algo(thr->env, WIDTH / NBTHREAD * thr->i, WIDTH / NBTHREAD
			* (thr->i + 1));
	pthread_exit(NULL);
}

void	is_texture_missing(t_wolf *env, int w, int h)
{
	env->wall1.im = mlx_xpm_file_to_image(env->mlx, "./textures/wall1.xpm",
	&w, &h);
	env->wall2.im = mlx_xpm_file_to_image(env->mlx, "./textures/wall2.xpm",
	&w, &h);
	env->wall3.im = mlx_xpm_file_to_image(env->mlx, "./textures/wall3.xpm",
	&w, &h);
	env->wall4.im = mlx_xpm_file_to_image(env->mlx, "./textures/wall4.xpm",
	&w, &h);
	env->sky.im = mlx_xpm_file_to_image(env->mlx, "./textures/sky.xpm",
	&w, &h);
	env->floor.im = mlx_xpm_file_to_image(env->mlx, "./textures/grass.xpm",
	&w, &h);
	if (!env->wall1.im || !env->wall2.im || !env->wall3.im || !env->wall4.im ||
	!env->floor.im || !env->sky.im)
	{
		ft_putstr("Texture missing\n");
		exit(0);
	}
}

int		define_wall_txt(t_wolf *env)
{
	env->wall1.imc = (int*)mlx_get_data_addr(env->wall1.im, &env->wall1.bpp,
	&env->wall1.imlen, &env->wall1.endi);
	env->wall1.width = 332;
	env->wall1.height = 332;
	env->wall2.imc = (int*)mlx_get_data_addr(env->wall2.im, &env->wall2.bpp,
	&env->wall2.imlen, &env->wall2.endi);
	env->wall2.width = 411;
	env->wall2.height = 411;
	env->wall3.imc = (int*)mlx_get_data_addr(env->wall3.im, &env->wall3.bpp,
	&env->wall3.imlen, &env->wall3.endi);
	env->wall3.width = 338;
	env->wall3.height = 338;
	env->wall4.imc = (int*)mlx_get_data_addr(env->wall4.im, &env->wall4.bpp,
	&env->wall4.imlen, &env->wall4.endi);
	env->wall4.width = 384;
	env->wall4.height = 384;
	return (0);
}

void	define_txt(t_wolf *env)
{
	env->sky.imc = (int*)mlx_get_data_addr(env->sky.im, &env->sky.bpp,
	&env->sky.imlen, &env->sky.endi);
	env->sky.width = 1192;
	env->floor.imc = (int*)mlx_get_data_addr(env->floor.im, &env->floor.bpp,
	&env->floor.imlen, &env->floor.endi);
	env->floor.width = 380;
	env->floor.height = 380;
}

void	multi_thread(t_wolf *env)
{
	pthread_t	thread[NBTHREAD];
	t_thread	thr[NBTHREAD];
	int			i;

	i = 0;
	is_texture_missing(env, WIDTH, HEIGHT);
	define_txt(env);
	define_wall_txt(env);
	while (i < NBTHREAD)
	{
		thr[i].env = env;
		thr[i].i = i;
		pthread_create(&thread[i], NULL, (void*)dda_thread, &thr[i]);
		i++;
	}
	while (i >= 0)
	{
		pthread_join(thread[i], NULL);
		i--;
	}
	mlx_put_image_to_window(env->mlx, env->win, env->img, 0, 0);
}
