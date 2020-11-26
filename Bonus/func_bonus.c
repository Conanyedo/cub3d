/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   func_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/13 13:26:43 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/26 08:26:02 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void			init(t_cub3d *cub)
{
	cub->path.no = NULL;
	cub->path.so = NULL;
	cub->path.we = NULL;
	cub->path.ea = NULL;
	cub->path.s = NULL;
	cub->path.f = NULL;
	cub->path.c = NULL;
	cub->map = NULL;
	cub->bullets = NULL;
	cub->heart = NULL;
	cub->weapons = NULL;
	cub->parse.x = 0;
	cub->parse.spawn = 0;
	cub->parse.line = NULL;
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
}

void			init_mlx(t_cub3d *cub)
{
	cub->mlx.p = mlx_init();
	cub->mlx.w = mlx_new_window(cub->mlx.p, cub->res.w, cub->res.h, "cub3d");
	cub->txt[0].img_ptr = mlx_xpm_file_to_image(cub->mlx.p, cub->path.no,
		&cub->txt[0].w, &cub->txt[0].h);
	cub->txt[1].img_ptr = mlx_xpm_file_to_image(cub->mlx.p, cub->path.we,
		&cub->txt[1].w, &cub->txt[1].h);
	cub->txt[2].img_ptr = mlx_xpm_file_to_image(cub->mlx.p, cub->path.so,
		&cub->txt[2].w, &cub->txt[2].h);
	cub->txt[3].img_ptr = mlx_xpm_file_to_image(cub->mlx.p, cub->path.ea,
		&cub->txt[3].w, &cub->txt[3].h);
	cub->txt[4].img_ptr = mlx_xpm_file_to_image(cub->mlx.p, cub->path.s,
		&cub->txt[4].w, &cub->txt[4].h);
	cub->txt[5].img_ptr = mlx_xpm_file_to_image(cub->mlx.p, cub->path.c,
		&cub->txt[5].w, &cub->txt[5].h);
	cub->txt[6].img_ptr = mlx_xpm_file_to_image(cub->mlx.p, cub->path.f,
		&cub->txt[6].w, &cub->txt[6].h);
}

void			checker(char **s, t_cub3d *cub, int i)
{
	int	j;

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
