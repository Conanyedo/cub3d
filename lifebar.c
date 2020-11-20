/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifebar.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 09:11:45 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/20 12:16:54 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	bar_color(t_cub3d *cub, int x, int y, int color)
{
	int		n;
	int		m;
	int		abrv;

	n = 0;
	while (n < cub->life.scale)
	{
		m = 0;
		while (m < cub->life.scale)
		{
			cub->img.img_data[((n + y) * cub->res.w + (m + x))] = color;
			if (cub->save == 1)
			{
				abrv = cub->res.h - cub->life.scale;
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

void	lifebar_bloc(t_cub3d *cub, int i, int j)
{
	if (cub->heart[i][j] == '1')
		bar_color(cub, cub->life.x, cub->life.y, 0x292929);
	else if (cub->heart[i][j] == '2')
		bar_color(cub, cub->life.x, cub->life.y, 0xf01d40);
	else if (cub->heart[i][j] == '3')
		bar_color(cub, cub->life.x, cub->life.y, 0x9c001a);
	else if (cub->heart[i][j] == '4')
		bar_color(cub, cub->life.x, cub->life.y, 0xbd0221);
	else if (cub->heart[i][j] == '5')
		bar_color(cub, cub->life.x, cub->life.y, 0xd1082a);
	else if (cub->heart[i][j] == '6')
		bar_color(cub, cub->life.x, cub->life.y, 0xffffff);
}

void	create_heart(t_cub3d *cub, int i)
{
	cub->heart = (char **)malloc(sizeof(char *) * 17 + 1);
	cub->heart[17] = NULL;
	while (cub->heart[++i])
	{
		cub->heart[i] = (char *)malloc(sizeof(char) * 17 + 1);
		ft_memset(cub->heart[i], 0, 17);
	}
	cub->heart[0] = "00111110001111100";
	cub->heart[1] = "01455551012222210";
	cub->heart[2] = "14445555155222221";
	cub->heart[3] = "14444555555566221";
	cub->heart[4] = "13444455555556221";
	cub->heart[5] = "13344445555555221";
	cub->heart[6] = "13334444555555521";
	cub->heart[7] = "11333444455555511";
	cub->heart[8] = "11133344445555111";
	cub->heart[9] = "01113334444551110";
	cub->heart[10] = "00111333444411100";
	cub->heart[11] = "00011133344111000";
	cub->heart[12] = "00001113331110000";
	cub->heart[13] = "00000111311100000";
	cub->heart[14] = "00000011111000000";
	cub->heart[15] = "00000001110000000";
	cub->heart[16] = "00000000100000000";
}

void	render_heart(t_cub3d *cub, int end, int j)
{
	int		i;

	while (cub->life.x < end)
	{
		cub->life.y = 0;
		i = 0;
		while (cub->life.y < cub->life.row)
		{
			lifebar_bloc(cub, i, j);
			i++;
			cub->life.y += cub->life.scale;
		}
		j++;
		cub->life.x += cub->life.scale;
	}
}

void	life_bar(t_cub3d *cub)
{
	int		j;
	int		heart_end;
	int		hearts;

	cub->life.hearts = 4;
	hearts = -1;
	cub->life.scale = cub->mini.scale / 2;
	cub->life.row = 17 * cub->life.scale;
	cub->life.x = cub->res.w - (cub->life.row * 4);
	create_heart(cub, hearts);
	while (++hearts < cub->life.hearts)
	{
		j = 0;
		heart_end = cub->life.x + cub->life.row;
		render_heart(cub, heart_end, j);
	}
}
