/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/02/12 19:13:25 by ybouddou          #+#    #+#             */
/*   Updated: 2020/10/22 13:46:50 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	draw(t_cub3d *cub)
{
	cub->img.img_ptr = mlx_new_image(cub->mlx.p, cub->res.w, cub->res.h);
	cub->img.img_data = (int *)mlx_get_data_addr(cub->img.img_ptr, &cub->img.bpp, &cub->img.size_line, &cub->img.endian);
	cub->ray = 0;
	while (cub->ray < cub->res.w)
	{
		calc(cub);
		sideDist(cub);
		hit(cub);
		wall(cub);
		render(cub);
	}
	if (cub->spriteNum)
		spriteRender(cub);
	mlx_put_image_to_window(cub->mlx.p, cub->mlx.w, cub->img.img_ptr, 0, 0);
}

int		deal_key(t_cub3d *cub)
{
	mlx_clear_window(cub->mlx.p, cub->mlx.w);
	movesUpDown(cub);
	moveSides(cub);
	look(cub);
	if (cub->keyboard[53])
		exit(0);
	draw(cub);
	return (0);
}

void	texture(t_cub3d *cub)
{
	//NO
	cub->txt[0].img_ptr = mlx_png_file_to_image(cub->mlx.p, cub->path.NO, &cub->txt[0].w, &cub->txt[0].h);
	cub->txt[0].img_data = (int*)mlx_get_data_addr(cub->txt[0].img_ptr, &cub->txt[0].bpp, &cub->txt[0].size_line, &cub->txt[0].endian);
	//WE
	cub->txt[1].img_ptr = mlx_png_file_to_image(cub->mlx.p, cub->path.WE, &cub->txt[1].w, &cub->txt[1].h);
	cub->txt[1].img_data = (int*)mlx_get_data_addr(cub->txt[1].img_ptr, &cub->txt[1].bpp, &cub->txt[1].size_line, &cub->txt[1].endian);
	//SO
	cub->txt[2].img_ptr = mlx_png_file_to_image(cub->mlx.p, cub->path.SO, &cub->txt[2].w, &cub->txt[2].h);
	cub->txt[2].img_data = (int*)mlx_get_data_addr(cub->txt[2].img_ptr, &cub->txt[2].bpp, &cub->txt[2].size_line, &cub->txt[2].endian);
	//EA
	cub->txt[3].img_ptr = mlx_png_file_to_image(cub->mlx.p, cub->path.EA, &cub->txt[3].w, &cub->txt[3].h);
	cub->txt[3].img_data = (int*)mlx_get_data_addr(cub->txt[3].img_ptr, &cub->txt[3].bpp, &cub->txt[3].size_line, &cub->txt[3].endian);
	//Sprite
	cub->txt[4].img_ptr = mlx_png_file_to_image(cub->mlx.p, cub->path.S, &cub->txt[4].w, &cub->txt[4].h);
	cub->txt[4].img_data = (int*)mlx_get_data_addr(cub->txt[4].img_ptr, &cub->txt[4].bpp, &cub->txt[4].size_line, &cub->txt[4].endian);
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
		else if (*cub->parse.line == 'S' || *cub->parse.line == 'N' || *cub->parse.line == 'W' ||
			*cub->parse.line == 'E')
			identifier(cub);
		else if (*cub->parse.line == ' ' || *cub->parse.line == '1' || *cub->parse.line == '0' ||
			(*cub->parse.line == '\0' && cub->parse.X > 0))
			map(cub);
		else if (*cub->parse.line)
			freeAll(cub);
	}
	if (cub->spriteNum)
		spriteInit(cub);
	if (cub->parse.mapline)
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
