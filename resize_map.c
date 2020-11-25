/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   resize_map.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/23 14:33:58 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/25 10:47:00 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	create_pixel(t_cub3d *cub, int x, int y, t_scale scale)
{
	int		i;
	int		j;
	int		abrv;

	i = 0;
	while (i < scale.y)
	{
		j = 0;
		while (j < scale.x)
		{
			cub->img.img_data[((i + y) * cub->res.w + (j + x))] = cub->color;
			if (cub->ac == 3)
			{
				abrv = cub->res.h - scale.y;
				cub->abrv = ((i + (abrv - y)) * cub->res.w + (j + (x)));
				cub->image[cub->abrv * 3 + 2] = cub->color >> 16;
				cub->image[cub->abrv * 3 + 1] = cub->color >> 8;
				cub->image[cub->abrv * 3 + 0] = cub->color;
			}
			j++;
		}
		i++;
	}
}

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

int		line_lenth(t_cub3d *cub, int i)
{
	int		prev_len;
	int		tmp;

	prev_len = (int)ft_strlen(cub->map[i]);
	if (prev_len > cub->len)
	{
		tmp = prev_len;
		prev_len = cub->len;
		cub->len = tmp;
	}
	return (cub->len);
}
