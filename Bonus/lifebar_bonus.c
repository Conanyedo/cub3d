/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lifebar_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 09:11:45 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/26 08:22:42 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

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

void	lifebar_color(t_cub3d *cub, int i, int j)
{
	cub->color = 0;
	if (cub->heart[i][j] == '1')
		cub->color = 0x292929;
	else if (cub->heart[i][j] == '2')
		cub->color = 0xf01d40;
	else if (cub->heart[i][j] == '3')
		cub->color = 0x9c001a;
	else if (cub->heart[i][j] == '4')
		cub->color = 0xbd0221;
	else if (cub->heart[i][j] == '5')
		cub->color = 0xd1082a;
	else if (cub->heart[i][j] == '6')
		cub->color = 0xffffff;
	if (cub->color)
		create_pixel(cub, cub->life.x, cub->life.y, cub->life.scale);
}

void	create_heart(t_cub3d *cub, int i)
{
	i = 0;
	cub->heart = (char **)malloc(sizeof(char *) * 17 + 1);
	cub->heart[17] = NULL;
	cub->heart[0] = ft_strdup("001111100011111000");
	cub->heart[1] = ft_strdup("014555510122222100");
	cub->heart[2] = ft_strdup("144455551552222210");
	cub->heart[3] = ft_strdup("144445555555662210");
	cub->heart[4] = ft_strdup("134444555555562210");
	cub->heart[5] = ft_strdup("133444455555552210");
	cub->heart[6] = ft_strdup("133344445555555210");
	cub->heart[7] = ft_strdup("113334444555555110");
	cub->heart[8] = ft_strdup("111333444455551110");
	cub->heart[9] = ft_strdup("011133344445511100");
	cub->heart[10] = ft_strdup("001113334444111000");
	cub->heart[11] = ft_strdup("000111333441110000");
	cub->heart[12] = ft_strdup("000011133311100000");
	cub->heart[13] = ft_strdup("000001113111000000");
	cub->heart[14] = ft_strdup("000000111110000000");
	cub->heart[15] = ft_strdup("000000011100000000");
	cub->heart[16] = ft_strdup("000000001000000000");
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
			lifebar_color(cub, i, j);
			i++;
			cub->life.y += cub->life.scale.y;
		}
		j++;
		cub->life.x += cub->life.scale.x;
	}
}

void	life_bar(t_cub3d *cub)
{
	int		j;
	int		heart_end;
	int		hearts;

	hearts = -1;
	cub->life.scale.x = cub->res.w * 3 / 100 / 18;
	cub->life.scale.y = cub->res.h * 5 / 100 / 17;
	cub->life.row = 17 * cub->life.scale.y;
	cub->life.len = 18 * cub->life.scale.x;
	cub->life.x = cub->res.w - (cub->life.len * 4);
	while (++hearts < cub->life.hearts)
	{
		j = 0;
		heart_end = cub->life.x + cub->life.len;
		render_heart(cub, heart_end, j);
	}
}
