/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bullets_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 11:54:03 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/26 08:22:54 by ybouddou         ###   ########.fr       */
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
	cub->bullets[10] = ft_strdup("3324422223330");
	cub->bullets[11] = ft_strdup("3324422223330");
	cub->bullets[12] = ft_strdup("3324422223330");
	cub->bullets[13] = ft_strdup("3324422223330");
	cub->bullets[14] = ft_strdup("3354455525330");
	cub->bullets[15] = ft_strdup("3324422223330");
	cub->bullets[16] = ft_strdup("3324422223330");
	cub->bullets[17] = ft_strdup("0111111111100");
	cub->bullets[18] = ft_strdup("3324422223330");
	cub->bullets[19] = ft_strdup("3333333333330");
	cub->bullets[20] = ft_strdup("0121000012100");
	cub->bullets[21] = ft_strdup("0010000001000");
}

void	create_bullet(t_cub3d *cub, int i)
{
	i = 0;
	cub->bullets = (char **)malloc(sizeof(char *) * 22 + 1);
	cub->bullets[22] = NULL;
	cub->bullets[0] = ft_strdup("0000666600000");
	cub->bullets[1] = ft_strdup("0006666660000");
	cub->bullets[2] = ft_strdup("0066978866000");
	cub->bullets[3] = ft_strdup("0667978886600");
	cub->bullets[4] = ft_strdup("0666766886600");
	cub->bullets[5] = ft_strdup("6679766688660");
	cub->bullets[6] = ft_strdup("6679766688660");
	cub->bullets[7] = ft_strdup("6667766886660");
	cub->bullets[8] = ft_strdup("0111111111100");
	cub->bullets[9] = ft_strdup("3324422223330");
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
