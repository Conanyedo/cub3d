/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 19:13:25 by ybouddou          #+#    #+#             */
/*   Updated: 2020/10/17 18:37:28 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx_png.h"
#include <math.h>
#include "get_next_line.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include "cub3d.h"


#define texWidth 64
#define texHeight 64

void	draw(t_cub3d *cub)
{
	
	cub->img.img_ptr = mlx_new_image(cub->mlx.p, cub->res.w, cub->res.h);
	cub->img.img_data = (int *)mlx_get_data_addr(cub->img.img_ptr, &cub->img.bpp, &cub->img.size_line, &cub->img.endian);
	
	cub->ray = 0;
	while (cub->ray < cub->res.w)
	{
		calc(cub);
		if (cub->rayDirX < 0)
		{
			cub->stepX = -1;
			cub->sideDistX = (cub->posX - cub->mapX) * cub->deltaDistX;
		}
		else
		{
			cub->stepX = 1;
			cub->sideDistX = (cub->mapX + 1.0 - cub->posX) * cub->deltaDistX;
		}
		if (cub->rayDirY < 0)
		{
			cub->stepY = -1;
			cub->sideDistY = (cub->posY - cub->mapY) * cub->deltaDistY;
		}
		else
		{
			cub->stepY = 1;
			cub->sideDistY = (cub->mapY + 1.0 - cub->posY) * cub->deltaDistY;
		}
		hit(cub);
		if (cub->side == 0 || cub->side == 2)
			cub->perpWallDist = (cub->mapX - cub->posX + (1 - cub->stepX) / 2) / cub->rayDirX;
		else
			cub->perpWallDist = (cub->mapY - cub->posY + (1 - cub->stepY) / 2) / cub->rayDirY;
			
		
		cub->lineHeight = (int)(cub->res.h / cub->perpWallDist);
		cub->drawStart = -cub->lineHeight / 2 + cub->res.h / 2;
		if(cub->drawStart < 0)
			cub->drawStart = 0;
		cub->drawEnd = cub->lineHeight / 2 + cub->res.h / 2;
		if(cub->drawEnd >= cub->res.h)
			cub->drawEnd = cub->res.h - 1;
		

		//calculate value of wallX
		double wallX; //where exactly the wall was hit
		if (cub->side == 0)
			wallX = cub->posY + cub->perpWallDist * cub->rayDirY;
		else
			wallX = cub->posX + cub->perpWallDist * cub->rayDirX;
		wallX -= floor((wallX));

		//x coordinate on the texture
		int texX = (int)(wallX * (double)(texWidth));
		if(cub->side == 0 && cub->rayDirX > 0) texX = texWidth - texX - 1;
		if(cub->side == 1 && cub->rayDirY < 0) texX = texWidth - texX - 1;
		// How much to increase the texture coordinate per screen pixel
      	double step = 1.0 * texHeight / cub->lineHeight;
      	// Starting texture coordinate
      	double texPos = (cub->drawStart - cub->res.h / 2 + cub->lineHeight / 2) * step;

		
		// int color;
		// if(cub->side == 0)
		// 	color = 0xFF2500;
		// else if(cub->side ==1)
		// 	color = 0x0044ed4;
		// else if(cub->side ==2)
		// 	color = 0x4EBDAD;
		// else if(cub->side ==3)
		// 	color = 0xF3CE00;
		while (cub->img.h < cub->res.h)
		{
			if (cub->img.h < cub->drawStart)
				cub->img.img_data[cub->img.h * cub->res.w + cub->ray] = createRGB(&cub->C);
			if (cub->img.h >= cub->drawStart && cub->img.h <= cub->drawEnd)
			{
				int texY = (int)texPos & (texHeight - 1);	
				texPos += step;
				if (cub->side == 0)//NO
				{
					//cub->img.img_data[cub->img.h * cub->res.w + cub->ray] = color;
					cub->img.img_data[cub->img.h * cub->res.w + cub->ray] = cub->txt[0].img_data[texX + texY * cub->txt[0].w];
				}
				else if (cub->side == 1)//WE
				{
					//cub->img.img_data[cub->img.h * cub->res.w + cub->ray] = color;
					cub->img.img_data[cub->img.h * cub->res.w + cub->ray] = cub->txt[1].img_data[texX + texY * cub->txt[1].w];
				}
				else if (cub->side == 2)//SO
				{
					//cub->img.img_data[cub->img.h * cub->res.w + cub->ray] = color;
					cub->img.img_data[cub->img.h * cub->res.w + cub->ray] = cub->txt[2].img_data[texX + texY * cub->txt[2].w];
				}
				else if (cub->side == 3)//EA
				{
					//cub->img.img_data[cub->img.h * cub->res.w + cub->ray] = color;
					cub->img.img_data[cub->img.h * cub->res.w + cub->ray] = cub->txt[3].img_data[texX + texY * cub->txt[3].w];
				}
			}
			if (cub->img.h > cub->drawEnd)
				cub->img.img_data[cub->img.h * cub->res.w + cub->ray] = createRGB(&cub->F);
			cub->img.h++;
		}
		cub->ray++;
	}
	mlx_put_image_to_window(cub->mlx.p, cub->mlx.w, cub->img.img_ptr, 0, 0);
}

int		deal_key(t_cub3d *cub)
{
	mlx_clear_window(cub->mlx.p, cub->mlx.w);
	moves(cub);
	look(cub);
	if(cub->keyboard[53])
		exit(0);
	draw(cub);
	return (0);
}

void	texture(t_cub3d *cub)
{
	cub->txt[0].img_ptr = mlx_png_file_to_image(cub->mlx.p, cub->path.NO, &cub->txt[0].w, &cub->txt[0].h);
	cub->txt[0].img_data = (int*)mlx_get_data_addr(cub->txt[0].img_ptr, &cub->txt[0].bpp, &cub->txt[0].size_line, &cub->txt[0].endian);
	
	cub->txt[1].img_ptr = mlx_png_file_to_image(cub->mlx.p, cub->path.WE, &cub->txt[1].w, &cub->txt[1].h);
	cub->txt[1].img_data = (int*)mlx_get_data_addr(cub->txt[1].img_ptr, &cub->txt[1].bpp, &cub->txt[1].size_line, &cub->txt[1].endian);
	
	cub->txt[2].img_ptr = mlx_png_file_to_image(cub->mlx.p, cub->path.SO, &cub->txt[2].w, &cub->txt[2].h);
	cub->txt[2].img_data = (int*)mlx_get_data_addr(cub->txt[2].img_ptr, &cub->txt[2].bpp, &cub->txt[2].size_line, &cub->txt[2].endian);
	
	cub->txt[3].img_ptr = mlx_png_file_to_image(cub->mlx.p, cub->path.EA, &cub->txt[3].w, &cub->txt[3].h);
	cub->txt[3].img_data = (int*)mlx_get_data_addr(cub->txt[3].img_ptr, &cub->txt[3].bpp, &cub->txt[3].size_line, &cub->txt[3].endian);
	/*
	cub->txt[4].img_ptr = mlx_xpm_file_to_image(cub->mlx.p, "bluestone.png", &cub->txt[4].w, &cub->txt[4].h);
	cub->txt[4].img_data = (int*)mlx_get_data_addr(cub->txt[4].img_ptr, &cub->txt[4].bpp, &cub->txt[4].size_line, &cub->txt[4].endian);
	*/	
}

void	parsing(t_cub3d *cub)
{
	while (cub->parse.r == 1)
	{
		cub->parse.nline++;
		cub->parse.r = get_next_line(cub->fd.lines, &cub->parse.line);
		if (*cub->parse.line == 'R')
			resolution(cub);
		else if (*cub->parse.line == 'F' || *cub->parse.line == 'C')
			FC(cub);
		else if (*cub->parse.line == 'S' || *cub->parse.line == 'N'|| *cub->parse.line == 'W' ||
			*cub->parse.line == 'E')
			identifier(cub);
		else if (*cub->parse.line == ' ' || *cub->parse.line == '1' || *cub->parse.line == '0' ||
			(*cub->parse.line == '\0' && cub->parse.X > 0))
			map(cub);
		else if (*cub->parse.line)
		{
			ft_free(cub->map);
			free(cub->path.NO);
			free(cub->path.SO);
			free(cub->path.EA);
			free(cub->path.WE);
			free(cub->path.S);
			ft_putstr_fd("Error\nWrong info\n", 2);
			exit (1);
		}
	}
	map_errors(cub);
	exist(cub);
}

int		main(int ac, char **av)
{
	if (ac == 2)
	{
		t_cub3d	cub;
		cub.fd.lines = open(av[1], O_RDONLY);
		
		init(&cub);
		parsing(&cub);
		printf("posX:%.f | posY:%.f\n",cub.posX, cub.posY);
		
		
		cub.res.w = 640;
		cub.res.h = 360;
		
		cub.mlx.p = mlx_init();
		cub.mlx.w = mlx_new_window(cub.mlx.p, cub.res.w, cub.res.h, "cub3d");
		
		texture(&cub);
		
		draw(&cub);
		mlx_hook(cub.mlx.w, 2, 0, key_pressed, &cub);
		mlx_hook(cub.mlx.w, 3, 0, key_released, &cub);
		mlx_loop_hook(cub.mlx.p, deal_key, &cub);
		mlx_loop(cub.mlx.p);
	}
	return (0);
}