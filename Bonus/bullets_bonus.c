/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bullets_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 11:54:03 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/23 18:30:16 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	bullet_color(t_cub3d *cub, int i, int j)
{
	cub->color = 0;
	if (cub->bullets[i][j] == '1')
		cub->color = 0x4f4005;
	else if (cub->bullets[i][j] == '2')
		cub->color = 0xf3c50c;
	else if (cub->bullets[i][j] == '3')
		cub->color = 0xc19c09;
	else if (cub->bullets[i][j] == '4')
		cub->color = 0xfae89e;
	else if (cub->bullets[i][j] == '5')
		cub->color = 0x010002;
	else if (cub->bullets[i][j] == '6')
		cub->color = 0x7d7d7d;
	else if (cub->bullets[i][j] == '7')
		cub->color = 0xcccccc;
	else if (cub->bullets[i][j] == '8')
		cub->color = 0x333333;
	else if (cub->bullets[i][j] == '9')
		cub->color = 0xededed;
	if (cub->color)
		create_pixel(cub, cub->bullet.x, cub->bullet.y, cub->bullet.scale);
}

void	complete_bullet(t_cub3d *cub)
{
	cub->bullets[10] = "3324422223330";
	cub->bullets[11] = "3324422223330";
	cub->bullets[12] = "3324422223330";
	cub->bullets[13] = "3324422223330";
	cub->bullets[14] = "3354455525330";
	cub->bullets[15] = "3324422223330";
	cub->bullets[16] = "3324422223330";
	cub->bullets[17] = "0111111111100";
	cub->bullets[18] = "3324422223330";
	cub->bullets[19] = "3333333333330";
	cub->bullets[20] = "0121000012100";
	cub->bullets[21] = "0010000001000";
}

void	create_bullet(t_cub3d *cub, int i)
{
	cub->bullets = (char **)malloc(sizeof(char *) * 22 + 1);
	cub->bullets[22] = NULL;
	while (cub->bullets[++i])
	{
		cub->bullets[i] = (char *)malloc(sizeof(char) * 13 + 1);
		ft_memset(cub->bullets[i], 0, 13);
	}
	cub->bullets[0] = "0000666600000";
	cub->bullets[1] = "0006666660000";
	cub->bullets[2] = "0066978866000";
	cub->bullets[3] = "0667978886600";
	cub->bullets[4] = "0666766886600";
	cub->bullets[5] = "6679766688660";
	cub->bullets[6] = "6679766688660";
	cub->bullets[7] = "6667766886660";
	cub->bullets[8] = "0111111111100";
	cub->bullets[9] = "3324422223330";
	complete_bullet(cub);
}

void	render_bullet(t_cub3d *cub, int j, int end)
{
	int		i;

	while (cub->bullet.x < end)
	{
		cub->bullet.y = cub->res.h - cub->bullet.row;
		i = 0;
		while (cub->bullet.y < cub->res.h)
		{
			bullet_color(cub, i, j);
			i++;
			cub->bullet.y += cub->bullet.scale.y;
		}
		j++;
		cub->bullet.x += cub->bullet.scale.x;
	}
}

void	bullets(t_cub3d *cub)
{
	int		j;
	int		bullets;
	int		end;

	if (cub->bullet.bullets)
	{
		bullets = -1;
		create_bullet(cub, bullets);
		cub->bullet.scale.x = cub->res.w * 3 / 100 / 13;
		cub->bullet.scale.y = cub->res.h / 10 / 22;
		cub->bullet.row = 22 * cub->bullet.scale.y;
		cub->bullet.len = 13 * cub->bullet.scale.x;
		cub->bullet.x = cub->res.w - (cub->bullet.len * 5);
		while (++bullets < cub->bullet.bullets)
		{
			j = 0;
			end = cub->bullet.x + cub->bullet.len;
			render_bullet(cub, j, end);
		}
	}
}
