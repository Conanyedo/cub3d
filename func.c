/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 13:26:43 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/20 12:21:57 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void			init(t_cub3d *cub)
{
	cub->rotatespeed = 0.03;
	cub->movespeed = 0.15;
	cub->path.no = NULL;
	cub->path.so = NULL;
	cub->path.we = NULL;
	cub->path.ea = NULL;
	cub->path.s = NULL;
	cub->map = NULL;
	cub->parse.x = 0;
	cub->parse.spawn = 0;
	cub->parse.line = NULL;
	cub->parse.colors = NULL;
	cub->parse.splitted = NULL;
	cub->rep.res = 0;
	cub->rep.no = 0;
	cub->rep.so = 0;
	cub->rep.we = 0;
	cub->rep.ea = 0;
	cub->rep.s = 0;
	cub->rep.f = 0;
	cub->rep.c = 0;
	cub->sprite_num = 0;
	cub->sprite_n = 0;
	cub->save = 1;
}

void			init_mlx(t_cub3d *cub)
{
	cub->mlx.p = mlx_init();
	cub->mlx.w = mlx_new_window(cub->mlx.p, cub->res.w, cub->res.h, "cub3d");
	cub->txt[0].img_ptr = mlx_xpm_file_to_image(cub->mlx.p, cub->path.no,
		&cub->txt[0].w, &cub->txt[0].h);
	cub->txt[0].img_data = (int*)mlx_get_data_addr(cub->txt[0].img_ptr,
		&cub->txt[0].bpp, &cub->txt[0].size_line, &cub->txt[0].endian);
	cub->txt[1].img_ptr = mlx_xpm_file_to_image(cub->mlx.p, cub->path.we,
		&cub->txt[1].w, &cub->txt[1].h);
	cub->txt[1].img_data = (int*)mlx_get_data_addr(cub->txt[1].img_ptr,
		&cub->txt[1].bpp, &cub->txt[1].size_line, &cub->txt[1].endian);
	cub->txt[2].img_ptr = mlx_xpm_file_to_image(cub->mlx.p, cub->path.so,
		&cub->txt[2].w, &cub->txt[2].h);
	cub->txt[2].img_data = (int*)mlx_get_data_addr(cub->txt[2].img_ptr,
		&cub->txt[2].bpp, &cub->txt[2].size_line, &cub->txt[2].endian);
	cub->txt[3].img_ptr = mlx_xpm_file_to_image(cub->mlx.p, cub->path.ea,
		&cub->txt[3].w, &cub->txt[3].h);
	cub->txt[3].img_data = (int*)mlx_get_data_addr(cub->txt[3].img_ptr,
		&cub->txt[3].bpp, &cub->txt[3].size_line, &cub->txt[3].endian);
	cub->txt[4].img_ptr = mlx_xpm_file_to_image(cub->mlx.p, cub->path.s,
		&cub->txt[4].w, &cub->txt[4].h);
	cub->txt[4].img_data = (int*)mlx_get_data_addr(cub->txt[4].img_ptr,
		&cub->txt[4].bpp, &cub->txt[4].size_line, &cub->txt[4].endian);
}

void			checker(char **s, t_cub3d *cub)
{
	int	i;
	int	j;

	i = 0;
	while (s[i])
	{
		j = 0;
		if (s[i][0] == '-')
			error_free("Error\nNegative number\n", cub, s);
		while (s[i][j])
		{
			if (s[i][j] < 48 || s[i][j] > 57)
				error_free("Error\nAnother char found\n", cub, s);
			j++;
		}
		i++;
	}
}

void			range(t_rgb *rgb, t_cub3d *cub)
{
	if (rgb->r > 255 || rgb->r < 0 || rgb->g > 255 || rgb->g < 0 ||
		rgb->b > 255 || rgb->b < 0)
		error_msg_free("Error\nRange is false\n", cub);
}

void			fc_checker(t_parse *parse, t_cub3d *cub)
{
	int	comma;
	int	i;

	i = 0;
	comma = 0;
	if (parse->splitted[2])
		error_free("Error\nAnother char found after F\n", cub, parse->splitted);
	while (parse->splitted[1][i])
	{
		if (parse->splitted[1][i] == ',')
			comma++;
		i++;
	}
	if (comma != 2)
		error_free("Error\nWrong format of rgb\n", cub, parse->splitted);
}

unsigned long	create_rgb(t_rgb *rgb)
{
	return ((rgb->r << 16) | (rgb->g << 8) | rgb->b);
}
