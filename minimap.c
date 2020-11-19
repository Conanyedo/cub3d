/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 12:23:00 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/19 14:01:40 by ybouddou         ###   ########.fr       */
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

	x = -1;
	cub->mini.sz = (cub->res.h * cub->res.w) / (cub->parse.x * cub->len) / 100;
	cub->mini.sz = (cub->mini.sz > 15) ? (cub->mini.sz / 2) : cub->mini.sz;
	cub->mini.sz = (cub->mini.sz < 4) ? 4 : cub->mini.sz;
	cub->mini.sz = (cub->mini.sz > 30) ? 30 : cub->mini.sz;
	cub->mini.scale = cub->mini.sz;
	cub->mini.len = (int)cub->len * cub->mini.scale;
	cub->mini.row = cub->parse.x * cub->mini.scale;
	cub->mini_map = (char **)malloc(sizeof(char *) * cub->parse.x + 2);
	while (++x < cub->parse.x)
	{
		cub->mini_map[x] = (char *)malloc(cub->len + 1);
		ft_memset(cub->mini_map[x], '\0', cub->len);
		y = -1;
		while (++y < (int)cub->len && cub->map[x][y])
			cub->mini_map[x][y] = cub->map[x][y];
		cub->mini_map[x][y] = '\0';
	}
	cub->mini_map[x] = NULL;
	cub->mini.show = 1;
}

void	bloc_color(t_cub3d *cub, int x, int y, int color)
{
	int		n;
	int		m;
	int		abrv;

	n = 0;
	while (n < cub->mini.scale)
	{
		m = 0;
		while (m < cub->mini.scale)
		{
			cub->img.img_data[((n + y) * cub->res.w + (m + x))] = color;
			if (cub->save == 1)
			{
				abrv = cub->res.h - cub->mini.scale;
				cub->abrv = ((n + (abrv - y)) * cub->res.w + (m + (x)));
				cub->image[cub->abrv * 3 + 2] = color >> 16;
				cub->image[cub->abrv * 3 + 1] = color >> 8;
				cub->image[cub->abrv * 3 + 0] = color;
			}
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
			minimap_bloc(cub, i, j);
			if (i == (int)cub->posx && j == (int)cub->posy)
				bloc_color(cub, cub->mini.x, cub->mini.y, 0x3a63b5);
			i++;
			cub->mini.y += cub->mini.scale;
		}
		j++;
		cub->mini.x += cub->mini.scale;
	}
}
