/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sprite.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 13:37:19 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/01 00:28:29 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	sprite(t_cub3d *cub, int x)
{
	cub->sprite[cub->spritePos].x = x;
	cub->sprite[cub->spritePos].y = cub->parse.Y;
	cub->spritePos++;
	cub->parse.Y++;
}

void	spriteInit(t_cub3d *cub)
{
	cub->ZBuffer = (double*)malloc((cub->res.w + 1) * sizeof(double));
	cub->spriteOrder = (int*)malloc((cub->spriteNum + 1) * sizeof(int));
	cub->spriteDist = (double*)malloc((cub->spriteNum + 1) * sizeof(double));
	cub->sprite = (t_sprite*)malloc((cub->spriteNum + 1) * sizeof(t_sprite));
}

void	swap(double *i, double *j)
{
	double		temp;

	temp = *i;
	*i = *j;
	*j = temp;
}

void	spriteSort(t_cub3d *cub)
{
	int		i;
	int		j;
	int		temp;

	i = 0;
	while (i < cub->spriteNum - 1)
	{
		j = 0;
		while (j < cub->spriteNum - i - 1)
		{
			if (cub->spriteDist[j] < cub->spriteDist[j + 1])
			{
				swap(&cub->sprite[j].x, &cub->sprite[j + 1].x);
				swap(&cub->sprite[j].y, &cub->sprite[j + 1].y);
				temp = cub->spriteOrder[j];
				cub->spriteOrder[j] = cub->spriteOrder[j + 1];
				cub->spriteOrder[j + 1] = temp;
				swap(&cub->spriteDist[j], &cub->spriteDist[j + 1]);
			}
			j++;
		}
		i++;
	}
}

void	spriteRender(t_cub3d *cub)
{
	while (cub->spriteN < cub->spriteNum)
	{
		cub->spriteOrder[cub->spriteN] = cub->spriteN;
		cub->spriteDist[cub->spriteN] = ((cub->posX - cub->sprite[cub->spriteN].x) * (cub->posX - cub->sprite[cub->spriteN].x)) +
			((cub->posY - cub->sprite[cub->spriteN].y) * (cub->posY - cub->sprite[cub->spriteN].y));
		cub->spriteN++;
	}
	spriteSort(cub);
	cub->spriteN = 0;
	while (cub->spriteN < cub->spriteNum)
	{
		cub->spriteX = cub->sprite[cub->spriteOrder[cub->spriteN]].x - cub->posX;
		cub->spriteY = cub->sprite[cub->spriteOrder[cub->spriteN]].y - cub->posY;
		cub->invDet = 1.0 / (cub->planeX * cub->dirY - cub->dirX * cub->planeY);
		cub->transformX = cub->invDet * (cub->dirY * cub->spriteX - cub->dirX * cub->spriteY);
		cub->transformY = cub->invDet * (-cub->planeY * cub->spriteX + cub->planeX * cub->spriteY);
		cub->spriteScreenX = (int)((cub->res.w / 2) * (1 + cub->transformX / cub->transformY));
		
		cub->spriteHeight = abs((int)(cub->res.h / cub->transformY));
		
		cub->drawStartY = -cub->spriteHeight / 2 + cub->res.h / 2;
		if (cub->drawStartY < 0)
			cub->drawStartY = 0;
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
		cub->spriteStripe = cub->drawStartX;
		while (cub->spriteStripe < cub->drawEndX)
		{
			cub->texX = (int)(256 * (cub->spriteStripe - (-cub->spriteWidth / 2 + cub->spriteScreenX)) * (cub->texWidth / cub->spriteWidth)) / 256;
			cub->spriteLine = cub->drawStartY;
			if (cub->transformY > 0 && cub->spriteStripe > 0 && cub->spriteStripe < cub->res.w &&
				cub->transformY < cub->ZBuffer[cub->spriteStripe])
			{
				while (cub->spriteLine < cub->drawEndY)
				{
					cub->d = (cub->spriteLine) * 256 - cub->res.h * 128 + cub->spriteHeight * 128;
					cub->texY = ((cub->d * cub->texHeight) / cub->spriteHeight) / 256;
					if (cub->txt[4].img_data[cub->texX + cub->texY * cub->txt[4].w])
						cub->img.img_data[cub->spriteLine * cub->res.w + cub->spriteStripe] = cub->txt[4].img_data[cub->texX + cub->texY * cub->txt[4].w];
					cub->spriteLine++;
				}
			}
			cub->spriteStripe++;
		}
		cub->spriteN++;
	}	
}