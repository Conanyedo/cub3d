/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 13:37:19 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/11 09:54:42 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	spriteposition(t_cub3d *cub, int x)
{
	cub->sprite[cub->spriteN].x = x + 0.5;
	cub->sprite[cub->spriteN].y = cub->parse.Y + 0.5;
	cub->spriteN++;
	cub->parse.Y++;
}

void	spritesort(t_cub3d *cub)
{
	t_sprite	tmp;
	int			i;
	int			j;

	i = 0;
	while (i < cub->spriteNum - 1)
	{
		j = 0;
		while (j < cub->spriteNum - i - 1)
		{
			if (cub->sprite[j].dist < cub->sprite[j + 1].dist)
			{
				tmp = cub->sprite[j];
				cub->sprite[j] = cub->sprite[j + 1];
				cub->sprite[j + 1] = tmp;
			}
			j++;
		}
		i++;
	}
}

void	spritedistance(t_cub3d *cub)
{
	int		num;

	cub->spriteN = 0;
	while (cub->spriteN < cub->spriteNum)
	{
		num = cub->spriteN;
		cub->sprite[cub->spriteN].order = cub->spriteN;
		cub->sprite[num].dist = pow(cub->posX - cub->sprite[num].x, 2) +
			pow(cub->posY - cub->sprite[cub->spriteN].y, 2);
		cub->spriteN++;
	}
	spritesort(cub);
	cub->spriteN = 0;
}

void	sprite(t_cub3d *cub)
{
	spritedistance(cub);
	while (cub->spriteN < cub->spriteNum)
	{
		cub->spriteX = cub->sprite[cub->spriteN].x - cub->posX;
		cub->spriteY = cub->sprite[cub->spriteN].y - cub->posY;
		cub->invDet = 1.0 / (cub->planeX * cub->dirY - cub->dirX * cub->planeY);
		cub->transformX = cub->invDet * (cub->dirY * cub->spriteX - cub->dirX * cub->spriteY);
		cub->transformY = cub->invDet * (-cub->planeY * cub->spriteX + cub->planeX * cub->spriteY);
		cub->spriteScreenX = (int)((cub->res.w / 2) * (1 + cub->transformX / cub->transformY));
		cub->spriteHeight = abs((int)(cub->res.h / cub->transformY));
		cub->drawStartY = -cub->spriteHeight / 2 + cub->res.h / 2;
		cub->drawStartY = (cub->drawStartY < 0) ? 0 : cub->drawStartY;
		cub->drawEndY = cub->spriteHeight / 2 + cub->res.h / 2;
		if (cub->drawEndY >= cub->res.h)
			cub->drawEndY = cub->res.h - 1;
		cub->spriteWidth = abs((int)(cub->res.h / (cub->transformY)));
		cub->drawStartX = -cub->spriteWidth / 2 + cub->spriteScreenX;
		if (cub->drawStartX < 0)
			cub->drawStartX = 0;
		cub->drawEndX = cub->spriteWidth / 2 + cub->spriteScreenX;
		if (cub->drawEndX >= cub->res.w)
			cub->drawEndX = cub->res.w - 1;
		spriterendering(cub);
		cub->spriteN++;
	}
}

void	spriterendering(t_cub3d *cub)
{
	while (cub->drawStartX < cub->drawEndX)
	{
		cub->texX = (int)(256 * (cub->drawStartX - (-cub->spriteWidth / 2 + cub->spriteScreenX)) * cub->texWidth / cub->spriteWidth) / 256;
		if (cub->transformY > 0 && cub->drawStartX > 0 && cub->drawStartX < cub->res.w &&
			cub->transformY < cub->ZBuffer[cub->drawStartX])
		{
			cub->spriteLine = cub->drawStartY;
			while (cub->spriteLine < cub->drawEndY)
			{
				cub->d = (cub->spriteLine) * 256 - cub->res.h * 128 + cub->spriteHeight * 128;
				cub->texY = ((cub->d * cub->texHeight) / cub->spriteHeight) / 256;
				if (cub->txt[4].img_data[cub->texX + cub->texY * cub->txt[4].w])
					cub->img.img_data[cub->spriteLine * cub->res.w + cub->drawStartX] = cub->txt[4].img_data[cub->texX + cub->texY * cub->txt[4].w];
				cub->spriteLine++;
			}
		}
		cub->drawStartX++;
	}
}
