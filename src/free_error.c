/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_error.c                                     .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: hmichel <hmichel@student.le-101.fr>        +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/02/10 04:53:27 by hmichel      #+#   ##    ##    #+#       */
/*   Updated: 2020/02/10 11:44:02 by hmichel     ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "../include/lemin.h"

void		free_no_solution(t_bfs *bfs, t_map *map)
{
	int i;

	i = -1;
	while (++i < bfs->nb_paths)
		free(bfs->queue[i]);
	i = -1;
	while (++i < map->inf.size_link)
		free(map->map_link[i]);
	i = -1;
	while (++i < map->inf.size_name)
	{
		free(bfs->mtx_diago[i]);
		free(bfs->mtx_state[i]);
		free(map->matrix[i]);
		free(map->map_name[i]);
		free(map->map_co[i]);
	}
	free(bfs->mtx_diago);
	free(bfs->mtx_state);
	free(map->matrix);
	free(map->map_co);
	free(map->map_link);
	free(map->map_name);
	free(bfs->queue);
	bfs->mtx_diago = NULL;
	bfs->mtx_state = NULL;
	bfs->queue = NULL;
	map->matrix = NULL;
}

int			free_line(char	**line)
{
	ft_strdel(line);
	return (-1);
}

int			free_print1(t_file_display **f_dis, t_name **name, t_link **link,
						t_map *map)
{
	t_name *name_temp;
	name_temp = *name;

	t_file_display *f_dis_temp;
	f_dis_temp = *f_dis;
	if (*(link) != NULL)
	{
		clear(name, link, f_dis);
		return (print_and_return(map->ret));
	}
	while (*f_dis)
	{
		f_dis_temp = (*f_dis)->next;
		free((*f_dis)->line);
		free(*f_dis);
		*f_dis = f_dis_temp;
	}
	while (name_temp)
	{
		name_temp = (*name)->next;
		free((*name)->name);
		free(*name);
		*name = name_temp;
	}
	return (print_and_return(map->ret));
}

int			free_print3(t_file_display **f_dis, t_name **name,
						t_link **link, t_map *map)
{
	int		i;

	i = -1;
	while (++i < map->inf.size_link)
		free(map->map_link[i]);
	i = -1;
	while (++i < map->inf.size_name)
	{
		free(map->matrix[i]);
		free(map->map_name[i]);
		free(map->map_co[i]);
	}
	free(map->matrix);
	free(map->map_co);
	free(map->map_link);
	free(map->map_name);
	clear(name, link, f_dis);
	return (print_and_return(map->ret));
}

int		ft_free_split(char ***split, int nb_words)
{
	//if (nb_words > 3)
	//{
		while (nb_words--)
		{
			free((*split)[nb_words]);
		}
		//free((*split)[0]);
		free((*split));
		return (-1);
	//}
	//free((*split)[0]);
	//free((*split)[1]);
	//free((*split)[2]);
	//free((*split)[0]);
	return (-1);
}

int			free_end_start(t_file_display **f_dis, t_name **name,
						t_link **link, t_map *map)
{
	int		i;

	i = -1;
	while (++i < map->inf.size_link)
		free(map->map_link[i]);
	i = -1;
	while (++i < map->inf.size_name)
	{
		free(map->matrix[i]);
		free(map->map_name[i]);
		free(map->map_co[i]);
	}
	free(map->matrix);
	free(map->map_co);
	free(map->map_link);
	free(map->map_name);
	clear(name, link, f_dis);
	return (0);
}
