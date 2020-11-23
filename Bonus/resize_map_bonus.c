/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_map_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:31:20 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/23 14:31:50 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	resize_rowmap(t_cub3d *cub)
{
	int		i;
	int		j;
	int		min_row;

	j = 0;
	min_row = cub->len;
	while (j < cub->len)
	{
		i = 0;
		while (i < cub->parse.x)
		{
			if (cub->map[i][j] == '1')
			{
				if (i < min_row)
					min_row = i;
				break ;
			}
			i++;
		}
		j++;
	}
	cub->mini.mini_row = min_row;
}

void	resize_map(t_cub3d *cub)
{
	int		i;
	int		j;
	int		min_len;

	i = 0;
	min_len = cub->parse.x;
	while (cub->map[i])
	{
		j = 0;
		while (cub->map[i][j])
		{
			if (cub->map[i][j] == '1')
			{
				if (j < min_len)
					min_len = j;
				break ;
			}
			j++;
		}
		i++;
	}
	cub->mini.mini_len = min_len;
	resize_rowmap(cub);
}
