/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/01 00:30:45 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/25 09:18:12 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	draw(t_cub3d *cub)
{
	cub->img.img_ptr = mlx_new_image(cub->mlx.p, cub->res.w, cub->res.h);
	cub->img.img_data = (int *)mlx_get_data_addr(cub->img.img_ptr,
		&cub->img.bpp, &cub->img.size_line, &cub->img.endian);
	cub->ray = 0;
	cub->texheight = 64;
	cub->texwidth = 64;
	cub->rotatespeed = 0.03;
	cub->movespeed = 0.15;
	floor_ceiling(cub);
	while (cub->ray < cub->res.w)
	{
		calc(cub);
		sidedist(cub);
		hit(cub);
		wall(cub);
		rendering(cub);
	}
	if (cub->sprite_num)
		sprite(cub);
	bonus(cub);
	cub->save = 0;
	mlx_put_image_to_window(cub->mlx.p, cub->mlx.w, cub->img.img_ptr, 0, 0);
}

int		deal_key(t_cub3d *cub)
{
	cub->weapon.fire = 0;
	mlx_destroy_image(cub->mlx.p, cub->img.img_ptr);
	mlx_clear_window(cub->mlx.p, cub->mlx.w);
	moves_up_down(cub);
	movesides(cub);
	look(cub);
	if (cub->keyboard[53])
		key_close(cub);
	bonus_keys(cub);
	draw(cub);
	return (0);
}

void	texture(t_cub3d *cub)
{
	int		i;

	i = -1;
	init_mlx(cub);
	while (++i < 7)
		cub->txt[i].img_data = (int*)mlx_get_data_addr(cub->txt[i].img_ptr,
			&cub->txt[i].bpp, &cub->txt[i].size_line, &cub->txt[i].endian);
	free_path(cub);
	cub->image = (char *)malloc(cub->res.w * cub->res.h * 3);
	cub->save = 1;
	cub->bullet.bullets = 5;
	system("afplay texture/Wolfenstein.mp3 &>/dev/null&");
}

void	parsing(t_cub3d *cub)
{
	cub->parse.r = 1;
	while (cub->parse.r == 1)
	{
		cub->parse.r = get_next_line(cub->fd.lines, &cub->parse.line);
		if (*cub->parse.line == 'R')
			resolution(cub);
		else if (*cub->parse.line == 'F' || *cub->parse.line == 'C')
			identifier(cub);
		else if (*cub->parse.line == 'S' || *cub->parse.line == 'N' ||
			*cub->parse.line == 'W' || *cub->parse.line == 'E')
			identifier(cub);
		else if (*cub->parse.line == ' ' || *cub->parse.line == '1' ||
			*cub->parse.line == '0')
			map(cub);
		else if (*cub->parse.line)
			error_msg_free("Error\nWrong info\n", cub);
		free(cub->parse.line);
	}
	if_sprite(cub);
	if (cub->parse.x)
		map_errors(cub);
	else
		error_msg_free("ERROR\nMap not found", cub);
	create_mini(cub);
}

int		main(int ac, char **av)
{
	t_cub3d	cub;

	if (ac >= 2 && ac <= 3)
	{
		cub.fd.lines = open(av[1], O_RDONLY);
		if (cub.fd.lines < 0)
			error_msg("Error\nInvalid file");
		init(&cub);
		parsing(&cub);
		texture(&cub);
		draw(&cub);
		bmp(&cub, ac, av);
		mlx_hook(cub.mlx.w, 2, 0, key_pressed, &cub);
		mlx_hook(cub.mlx.w, 3, 0, key_released, &cub);
		mlx_hook(cub.mlx.w, 17, 0, key_close, &cub);
		mlx_loop_hook(cub.mlx.p, deal_key, &cub);
		mlx_loop(cub.mlx.p);
		ft_free(cub.map);
	}
	else
		error_msg("Error\nInvalid params");
	return (0);
}
