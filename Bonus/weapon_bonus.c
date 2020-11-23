/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   weapon_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 22:13:28 by root              #+#    #+#             */
/*   Updated: 2020/11/23 18:40:13 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	color_weapon(t_cub3d *cub, int i, int j)
{
	if (cub->weapons[i][j] == '8')
		cub->color = 0xe98c57;
	else if (cub->weapons[i][j] == '9')
		cub->color = 0xfcb081;
	else if (cub->weapons[i][j] == '+')
		cub->color = 0xfcd9c5;
	else if (cub->weapons[i][j] == '-')
		cub->color = 0x0d0c0d;
	else if (cub->weapons[i][j] == '*')
		cub->color = 0x1a1a1a;
	else if (cub->weapons[i][j] == '#')
		cub->color = 0xfcfc54;
	else if (cub->weapons[i][j] == 'r')
		cub->color = 0xec0000;
	else if (cub->weapons[i][j] == 'R')
		cub->color = 0x980000;
	else if (cub->weapons[i][j] == 'p')
		cub->color = 0xfc5c5c;
	else if (cub->weapons[i][j] == 'w')
		cub->color = 0xfc9c9c;
}

void	weapon_color(t_cub3d *cub, int i, int j)
{
	cub->color = 0;
	if (cub->weapons[i][j] == '1')
		cub->color = 0x999999;
	else if (cub->weapons[i][j] == '2')
		cub->color = 0xa9a9a9;
	else if (cub->weapons[i][j] == '3')
		cub->color = 0x7d7d7d;
	else if (cub->weapons[i][j] == '4')
		cub->color = 0x646464;
	else if (cub->weapons[i][j] == '5')
		cub->color = 0x464646;
	else if (cub->weapons[i][j] == '6')
		cub->color = 0xa9693e;
	else if (cub->weapons[i][j] == '7')
		cub->color = 0x915c31;
	else
		color_weapon(cub, i, j);
	if (cub->color)
		create_pixel(cub, cub->weapon.x, cub->weapon.y, cub->weapon.scale);
}

void	complete_weapon(t_cub3d *cub)
{
	cub->weapons[10] = "000085*1555-*-670000";
	cub->weapons[11] = "000899*1555-*7660000";
	cub->weapons[12] = "00089+7----**7667000";
	cub->weapons[13] = "00089++6777688666000";
	cub->weapons[14] = "00899++++99886677000";
	cub->weapons[15] = "008989+++99886677000";
	cub->weapons[16] = "00898699999888667000";
	cub->weapons[17] = "00899889998888667000";
	cub->weapons[18] = "00111286888881113300";
	cub->weapons[19] = "01221344667712211340";
	cub->weapons[20] = "12211334554312211134";
}

void	create_weapon(t_cub3d *cub)
{
	int		i;

	i = -1;
	cub->weapons = (char **)malloc(sizeof(char *) * 21 + 1);
	cub->weapons[21] = NULL;
	while (cub->weapons[++i])
	{
		cub->weapons[i] = (char *)malloc(sizeof(char) * 20 + 1);
		ft_memset(cub->weapons[i], 0, 20);
	}
	cub->weapons[0] = "000000000-0000000000";
	cub->weapons[1] = "00000000434000000000";
	cub->weapons[2] = "00000004121400000000";
	cub->weapons[3] = "00000004121400000000";
	cub->weapons[4] = "00000011414110000000";
	cub->weapons[5] = "00000512555434000000";
	cub->weapons[6] = "00000512434414000000";
	cub->weapons[7] = "00000512111315000000";
	cub->weapons[8] = "00000541222435000000";
	cub->weapons[9] = "000005*1444-*-600000";
	complete_weapon(cub);
}

void	weapon(t_cub3d *cub)
{
	int		j;
	int		i;
	int		end;

	create_weapon(cub);
	cub->weapon.scale.x = cub->res.w / 5 / 20;
	cub->weapon.scale.y = cub->res.h / 3 / 21;
	cub->weapon.row = 21 * cub->weapon.scale.y;
	cub->weapon.len = 20 * cub->weapon.scale.x;
	cub->weapon.x = cub->res.w / 2 - (cub->weapon.len / 2);
	end = cub->res.w / 2 + (cub->weapon.len / 2);
	j = 0;
	while (cub->weapon.x < end)
	{
		cub->weapon.y = cub->res.h - cub->weapon.row;
		i = 0;
		while (cub->weapon.y < cub->res.h)
		{
			weapon_color(cub, i, j);
			i++;
			cub->weapon.y += cub->weapon.scale.y;
		}
		j++;
		cub->weapon.x += cub->weapon.scale.x;
	}
}
