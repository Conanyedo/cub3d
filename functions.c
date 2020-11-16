/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:52:06 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/16 13:29:58 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		key_close(t_cub3d *cub)
{
	mlx_clear_window(cub->mlx.p, cub->mlx.w);
	system("rm -rf a.out >/dev/null 2>&1");
	exit(0);
	return (0);
}

void	if_sprite(t_cub3d *cub)
{
	if (cub->sprite_num)
	{
		cub->sprite_buf = (double *)malloc((cub->res.w + 1) * sizeof(double));
		cub->sprite = malloc((cub->sprite_num + 1) * sizeof(t_sprite));
	}
}

void	free_path(t_cub3d *cub)
{
	free(cub->path.no);
	free(cub->path.so);
	free(cub->path.ea);
	free(cub->path.we);
	free(cub->path.s);
}

void	wallrendering(t_cub3d *cub)
{
	cub->tex_y = (int)cub->texpos;
	cub->texpos += cub->step;
	if (cub->side == 0)
		cub->color = cub->txt[2].img_data[cub->tex_x + cub->tex_y
			* cub->txt[2].w];
	else if (cub->side == 1)
		cub->color = cub->txt[3].img_data[cub->tex_x + cub->tex_y *
			cub->txt[3].w];
	else if (cub->side == 2)
		cub->color = cub->txt[0].img_data[cub->tex_x + cub->tex_y *
			cub->txt[0].w];
	else if (cub->side == 3)
		cub->color = cub->txt[1].img_data[cub->tex_x + cub->tex_y *
			cub->txt[1].w];
	cub->img.img_data[cub->img.h * cub->res.w + cub->ray] = cub->color;
	if (cub->save == 1)
	{
		cub->image[(cub->ray + (cub->drawend - cub->bmp_pos) * cub->res.w)
			* 3 + 2] = cub->color >> 16;
		cub->image[(cub->ray + (cub->drawend - cub->bmp_pos) * cub->res.w)
			* 3 + 1] = cub->color >> 8;
		cub->image[(cub->ray + (cub->drawend - cub->bmp_pos) * cub->res.w)
			* 3 + 0] = cub->color;
		cub->bmp_pos++;
	}
}

void	sprite_image(t_cub3d *cub)
{
	cub->d = (cub->spriteline) * 256 - cub->res.h * 128 +
		cub->spriteheight * 128;
	cub->tex_y = ((cub->d * cub->texheight) / cub->spriteheight) / 256;
	if (cub->txt[4].img_data[cub->tex_x + cub->tex_y * cub->txt[4].w])
	{
		cub->img.img_data[cub->spriteline * cub->res.w + cub->drawstartx] =
			cub->txt[4].img_data[cub->tex_x + cub->tex_y * cub->txt[4].w];
		if (cub->save == 1)
		{
			cub->abrv = ((cub->drawendy - cub->bmp_pos) * cub->res.w +
				cub->drawstartx);
			cub->image[cub->abrv * 3 + 2] = cub->txt[4].img_data[cub->tex_x +
				cub->tex_y * cub->txt[4].w] >> 16;
			cub->image[cub->abrv * 3 + 1] = cub->txt[4].img_data[cub->tex_x +
				cub->tex_y * cub->txt[4].w] >> 8;
			cub->image[cub->abrv * 3 + 0] = cub->txt[4].img_data[cub->tex_x +
				cub->tex_y * cub->txt[4].w];
		}
	}
	cub->bmp_pos++;
}
