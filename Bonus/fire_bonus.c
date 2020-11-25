/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fire_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 11:09:25 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/25 13:50:54 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	color_fire(t_cub3d *cub, int i, int j)
{
	if (cub->shot[i][j] == '8')
		cub->color = 0xe98c57;
	else if (cub->shot[i][j] == '9')
		cub->color = 0xfcb081;
	else if (cub->shot[i][j] == '+')
		cub->color = 0xfcd9c5;
	else if (cub->shot[i][j] == '-')
		cub->color = 0x0d0c0d;
	else if (cub->shot[i][j] == '*')
		cub->color = 0x1a1a1a;
	else if (cub->shot[i][j] == '#')
		cub->color = 0xfcfc54;
	else if (cub->shot[i][j] == 'r')
		cub->color = 0xec0000;
	else if (cub->shot[i][j] == 'R')
		cub->color = 0x980000;
	else if (cub->shot[i][j] == 'p')
		cub->color = 0xfc5c5c;
	else if (cub->shot[i][j] == 'w')
		cub->color = 0xfc9c9c;
}

void	fire_color(t_cub3d *cub, int i, int j)
{
	cub->color = 0;
	if (cub->shot[i][j] == '1')
		cub->color = 0x999999;
	else if (cub->shot[i][j] == '2')
		cub->color = 0xa9a9a9;
	else if (cub->shot[i][j] == '3')
		cub->color = 0x7d7d7d;
	else if (cub->shot[i][j] == '4')
		cub->color = 0x646464;
	else if (cub->shot[i][j] == '5')
		cub->color = 0x464646;
	else if (cub->shot[i][j] == '6')
		cub->color = 0xa9693e;
	else if (cub->shot[i][j] == '7')
		cub->color = 0x915c31;
	else
		color_fire(cub, i, j);
	if (cub->color)
		create_pixel(cub, cub->fire.x, cub->fire.y, cub->weapon.scale);
}

void	complete_fire(t_cub3d *cub)
{
	cub->shot[10] = "000000512555434000000000";
	cub->shot[11] = "000000512434414000000000";
	cub->shot[12] = "000000512111315000000000";
	cub->shot[13] = "000000541222435000000000";
	cub->shot[14] = "0000005*1444-*-600000000";
	cub->shot[15] = "0000085*1555-*-670000000";
	cub->shot[16] = "0000899*1555-*7660000000";
	cub->shot[17] = "000089+7----**7667000000";
	cub->shot[18] = "000089++6777688666000000";
	cub->shot[19] = "000899++++99886677000000";
	cub->shot[20] = "0008989+++99886677000000";
	cub->shot[21] = "000898699999888667000000";
	cub->shot[22] = "000899889998888667000000";
	cub->shot[23] = "000111286888881113300000";
	cub->shot[24] = "001221344667712211340000";
	cub->shot[25] = "012211334554312211134000";
	cub->shot[26] = "122113344554331333114500";
	cub->shot[27] = "431133444554343122113450";
	cub->shot[28] = "122334444554443332234455";
}

void	create_fire(t_cub3d *cub, int i)
{
	cub->shot = (char **)malloc(sizeof(char *) * 29 + 1);
	cub->shot[29] = NULL;
	while (cub->shot[++i])
	{
		cub->shot[i] = (char *)malloc(sizeof(char) * 24 + 1);
		ft_memset(cub->shot[i], 0, 24);
	}
	cub->shot[0] = "0000000000R0000000000000";
	cub->shot[1] = "0000000000R0000000000000";
	cub->shot[2] = "000000000RrR000000000000";
	cub->shot[3] = "000000r00rwr00r000000000";
	cub->shot[4] = "0000000pppwppp0000000000";
	cub->shot[5] = "0000000rww#wpr0000000000";
	cub->shot[6] = "000000Rp#434#pr000000000";
	cub->shot[7] = "00000Rpw41214wpR00000000";
	cub->shot[8] = "000000Rr41214rR000000000";
	cub->shot[9] = "000000011414110000000000";
	complete_fire(cub);
}

void	fire(t_cub3d *cub)
{
	int		j;
	int		i;
	int		end;

	i = 0;
	cub->fire.row = 29 * cub->weapon.scale.y;
	cub->fire.len = 24 * cub->weapon.scale.x;
	cub->fire.x = cub->res.w / 2 - (cub->fire.len / 2);
	end = cub->res.w / 2 + (cub->fire.len / 2);
	j = 0;
	while (cub->fire.x < end)
	{
		cub->fire.y = cub->res.h - cub->fire.row;
		i = 0;
		while (cub->fire.y < cub->res.h)
		{
			fire_color(cub, i, j);
			i++;
			cub->fire.y += cub->weapon.scale.y;
		}
		j++;
		cub->fire.x += cub->weapon.scale.x;
	}
}
