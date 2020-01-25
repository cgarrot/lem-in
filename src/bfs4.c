/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   bfs4.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/20 08:26:29 by hmichel      #+#   ##    ##    #+#       */
/*   Updated: 2020/01/25 08:21:07 by hmichel     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"
#include <stdio.h>
/*
static int	ft_init_tripaths(t_tripaths *tri, t_bfs *bfs)
{
	int		i;
	int		j;

	i = -1;
	if (!(tri = (t_tripaths *)malloc(sizeof(t_tripaths))))
		return (FAILURE);
	if (!(tri->paths = (t_path **)malloc(sizeof(t_path *) * bfs->nb_paths)))
		return (FAILURE);
	while (++i < bfs->end_links)
	{
		j = -1;
		if (!(tri->paths[i] = (t_path *)malloc(sizeof(t_path) * bfs->end_links)))
			return (FAILURE);
		while (++j < bfs->end_links)
		{
			tri->paths[i][j].path = NULL;
			tri->paths[i][j].size = 0;
		}
	}
	return (SUCCESS);
}*/

void			get_nb_sub_path(t_bfs *bfs, t_temp_paths tp, t_tripaths *tri)
{
	int 	i;
	int		path;
	int 	count;

	path  = -1;
	while (++path < bfs->nb_paths)
	{
		count = 0;
		i = -1;
		while (++i < bfs->end_links)
		{
			if (bfs->mtx_state[tp.sub_ends[i]][path] != -1)
				count++;
		}
		printf("count = %d\n", count);
		tri->nb_subs[path] = count;
	}
}

static int	ft_sub_ends(t_bfs *bfs, t_temp_paths *tp)
{
	int		i;
	int		j;

	i = -1;
	j = -1;
	if (!(tp->sub_ends = (int *)malloc(sizeof(int) * bfs->end_links)))
		return (FAILURE);
	while (++i < bfs->size_diago)
	{
		if (bfs->mtx_diago[bfs->end][i])
			tp->sub_ends[++j] = i;
	}
	return (SUCCESS);
}

static int	ft_states_to_paths(t_bfs *bfs, t_tripaths *tri, t_temp_paths tp)
{
	int		step;
	int		prev;
	int		i_state;

	//printf("bfs->mtx_state[tp.sub_ends[tp.sub_paths]][tp.act_path] = %d et tp.sub_ends[tp.sub_paths] = %d\n", bfs->mtx_state[tp.sub_ends[tp.sub_paths]][tp.act_path], tp.sub_ends[tp.sub_paths]);
	if (bfs->mtx_state[tp.sub_ends[tp.sub_paths]][tp.act_path] == -1)
	{
		//printf("tp.subpaths : %d\n", tp.sub_paths);
		//printf("bfs->mtx_state[%d][%d]\n", tp.sub_ends[tp.sub_paths], tp.act_path);
		//printf("cancel path\n");
		return (SUCCESS);
	}
	tri->paths[tp.act_path][tp.sub_paths].size = bfs->mtx_state[tp.sub_ends[tp.sub_paths]][tp.act_path] + 2;
	//printf("tp.act_path = %d, tp.sub_paths = %d, tri->paths[tp.act_path][tp.sub_paths].size = %d\n", tp.act_path, tp.sub_paths, tri->paths[tp.act_path][tp.sub_paths].size);
	if (!(tri->paths[tp.act_path][tp.sub_paths].path = (int *)malloc(sizeof(int) *
		tri->paths[tp.act_path][tp.sub_paths].size)))
		return (FAILURE);
	step = bfs->mtx_state[tp.sub_ends[tp.sub_paths]][tp.act_path];
	//printf("tp.act_path = %d, tp.sub_paths = %d, tp.sub_ends[tp.sub_paths] = %d, bfs->mtx_state[tp.sub_ends[tp.sub_paths]][tp.act_path] = %d\n", tp.act_path, tp.sub_paths, tp.sub_ends[tp.sub_paths], bfs->mtx_state[tp.sub_ends[tp.sub_paths]][tp.act_path]);
	tri->paths[tp.act_path][tp.sub_paths].path[tri->paths[tp.act_path][tp.sub_paths].size - 1] = bfs->end;
	tri->paths[tp.act_path][tp.sub_paths].path[tri->paths[tp.act_path][tp.sub_paths].size - 2] = tp.sub_ends[tp.sub_paths];
	prev = tp.sub_ends[tp.sub_paths];
	while (--step)
	{
		i_state = -1;
		while (++i_state < bfs->size_diago)
		{
			if (bfs->mtx_state[i_state][tp.act_path] == step && bfs->mtx_diago[i_state][prev]) //tester swap ordre conditions pour opti un peu
			{
				tri->paths[tp.act_path][tp.sub_paths].path[step] = i_state;
				prev = i_state;
				break ;
			}
		}
	}
	//printf ("path OK\n");
	tri->paths[tp.act_path][tp.sub_paths].path[0] = bfs->start;
	//printf("tri->nb_subs[%d] = %d\n", tp.act_path, tri->nb_subs[tp.act_path]);
	ft_putintstr(tri->paths[tp.act_path][tp.sub_paths].path, tri->paths[tp.act_path][tp.sub_paths].size);
	//printf("[zob]tri->count_paths = %d \n", tri->count_paths);
	tri->count_paths++;
	return (SUCCESS);
}

int			ft_takepaths(t_bfs *bfs, t_tripaths *tri, t_res	*res)
{
	t_temp_paths tp;
	int		i;
	int		j;

	i = -1;
	res = NULL;
	//tri->count_paths = 0;
	if (!(tri = (t_tripaths *)malloc(sizeof(t_tripaths))))
		return (FAILURE);
	if (!(tri->paths = (t_path **)malloc(sizeof(t_path *) * bfs->nb_paths)))
		return (FAILURE);
	while (++i < bfs->nb_paths)
	{
		j = -1;
		if (!(tri->paths[i] = (t_path *)malloc(sizeof(t_path) * bfs->end_links)))
			return (FAILURE);
		while (++j < bfs->end_links)
		{
			tri->paths[i][j].path = NULL;
			tri->paths[i][j].size = 0;
		}
	}
	if (!(tri->nb_subs = (int *)malloc(sizeof(int) * bfs->nb_paths)))
		return (FAILURE);
	//if (!ft_init_tripaths(tri, bfs))
	//	return (FAILURE);
	if (!ft_sub_ends(bfs, &tp))
		return (FAILURE);
	get_nb_sub_path(bfs, tp, tri);
	//printf("tnb_subs:\n");
	ft_putintstr(tri->nb_subs, bfs->nb_paths);
	//ft_putintstr(tp.sub_ends, bfs->end_links);
	tp.act_path = -1;
	while (++tp.act_path < bfs->nb_paths)
	{
		tp.sub_paths = -1;
		while (++tp.sub_paths < bfs->end_links)//tri->nb_subs[tp.act_path])
			if (!ft_states_to_paths(bfs, tri, tp))
				return (FAILURE);
	}
	//printf("count_paths = %d\n", tri->count_paths);
	//ft_printallpaths(*tri, *bfs);
	//bfs->count_paths = tri->count_paths;
	//tri_to_res(res, tri, bfs);
	return (SUCCESS);
}