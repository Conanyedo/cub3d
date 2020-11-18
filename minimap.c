/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 12:23:00 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/18 14:05:34 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	line_lenth(t_cub3d *cub, int i)
{
	size_t	prev_len;
	size_t	tmp;

	prev_len = ft_strlen(cub->map[i]);
	if (prev_len > cub->len)
	{
		tmp = prev_len;
		prev_len = cub->len;
		cub->len = tmp;
	}
	return (cub->len);
}

void	creat_mini(t_cub3d *cub)
{
	int		x;
	int		y;

	x = 0;
	y = 0;
	cub->mini.scale = cub->res.h * cub->res.w * 0.000004;
	cub->mini.len = (int)cub->len * cub->mini.scale;
	cub->mini.row = cub->parse.x * cub->mini.scale;
	cub->mini_map = (char **)malloc(sizeof(char *) * cub->parse.x + 2);
	while (x < cub->parse.x)
	{
		cub->mini_map[x] = (char *)malloc(cub->len + 1);
		ft_memset(cub->mini_map[x], '\0', cub->len);
		y = 0;
		while (y < (int)cub->len && cub->map[x][y])
		{
			cub->mini_map[x][y] = cub->map[x][y];
			y++;
		}
		cub->mini_map[x][y] = '\0';
		x++;
	}
	cub->mini_map[x] = NULL;
}

void	bloc_color(t_cub3d *cub, int x, int y, int color)
{
	int		n;
	int		m;

	n = 0;
	while (n < cub->mini.scale)
	{
		m = 0;
		while (m < cub->mini.scale)
		{
			cub->mini.img_data[((n + y) * cub->mini.len + (m + x))] = color;
			// if (cub->save == 1)
			// {
			// 	cub->abrv = ((n + y) * cub->mini.len + (m + x));
			// 	cub->image[cub->abrv * 3 + 2] = color >> 16;
			// 	cub->image[cub->abrv * 3 + 1] = color >> 8;
			// 	cub->image[cub->abrv * 3 + 0] = color;
			// }
			m++;
		}
		n++;
	}
}

void	minimap_bloc(t_cub3d *cub, int i, int j)
{
	if (cub->mini_map[i][j] == '1')
		bloc_color(cub, cub->mini.x, cub->mini.y, 0x292929);
	else if (cub->mini_map[i][j] == '0')
		bloc_color(cub, cub->mini.x, cub->mini.y, 0xededed);
	else if (cub->mini_map[i][j] == '2')
		bloc_color(cub, cub->mini.x, cub->mini.y, 0xeb8252);
	else
		bloc_color(cub, cub->mini.x, cub->mini.y, 0xc4c4c4);
}

void	minimap(t_cub3d *cub)
{
	int		i;
	int		j;

	j = 0;
	cub->mini.x = 0;
	while (cub->mini.x < cub->mini.len)
	{
		cub->mini.y = 0;
		i = 0;
		while (cub->mini.y < cub->mini.row)
		{
			if (i == (int)cub->posx && j == (int)cub->posy)
				bloc_color(cub, cub->mini.x, cub->mini.y, 0x3a63b5);
			else
				minimap_bloc(cub, i, j);
			i++;
			cub->mini.y += cub->mini.scale;
		}
		j++;
		cub->mini.x += cub->mini.scale;
	}
}
