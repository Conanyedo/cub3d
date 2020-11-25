/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 12:23:00 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/25 10:45:52 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	fill_min(t_cub3d *cub, int row, int len)
{
	int		i;
	int		j;
	int		x;
	int		y;

	i = 0;
	cub->mini_map = (char **)malloc(sizeof(char *) * (cub->parse.x - row + 2));
	x = row;
	while (x < cub->parse.x)
	{
		cub->mini_map[i] = (char *)malloc(cub->len - len + 1);
		ft_memset(cub->mini_map[i], '\0', cub->len - len);
		y = len;
		j = 0;
		while (y < (int)cub->len && cub->map[x][y])
		{
			cub->mini_map[i][j] = cub->map[x][y];
			j++;
			y++;
		}
		cub->mini_map[i][j] = '\0';
		i++;
		x++;
	}
	cub->mini_map[i] = NULL;
}

void	create_mini(t_cub3d *cub)
{
	int		row;
	int		len;

	resize_map(cub);
	row = cub->mini.mini_row;
	len = cub->mini.mini_len;
	cub->mini.scale.x = cub->res.w / 5 / (cub->len - len);
	cub->mini.scale.y = cub->res.h / 5 / (cub->parse.x - row);
	cub->mini.scale.x = cub->mini.scale.x <= 2 ? 3 : cub->mini.scale.x;
	cub->mini.scale.y = cub->mini.scale.y <= 2 ? 3 : cub->mini.scale.y;
	cub->mini.len = (cub->len - len) * cub->mini.scale.x;
	cub->mini.row = (cub->parse.x - row) * cub->mini.scale.y;
	fill_min(cub, row, len);
	cub->mini.show = 1;
}

void	minimap_color(t_cub3d *cub, int i, int j)
{
	cub->color = 0;
	if (cub->mini_map[i][j] == '1')
		cub->color = 0x292929;
	else if (cub->mini_map[i][j] == '0')
		cub->color = 0xededed;
	else if (cub->mini_map[i][j] == '2')
		cub->color = 0xeb8252;
	else if (cub->mini_map[i][j] == '3')
		cub->color = 0xeb8252;
	else if (cub->mini_map[i][j] == '4')
		cub->color = 0xeb8252;
	if (cub->color)
		create_pixel(cub, cub->mini.x, cub->mini.y, cub->mini.scale);
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
			minimap_color(cub, i, j);
			if (i + cub->mini.mini_row == (int)cub->posx &&
				j + cub->mini.mini_len == (int)cub->posy)
			{
				cub->color = 0x3a63b5;
				create_pixel(cub, cub->mini.x, cub->mini.y, cub->mini.scale);
			}
			i++;
			cub->mini.y += cub->mini.scale.y;
		}
		j++;
		cub->mini.x += cub->mini.scale.x;
	}
}
