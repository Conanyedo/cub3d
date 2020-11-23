/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fire_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 11:09:25 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/23 18:26:17 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	complete_fire(t_cub3d *cub)
{
	cub->weapons[10] = "000000512555434000000000";
	cub->weapons[11] = "000000512434414000000000";
	cub->weapons[12] = "000000512111315000000000";
	cub->weapons[13] = "000000541222435000000000";
	cub->weapons[14] = "0000005*1444-*-600000000";
	cub->weapons[15] = "0000085*1555-*-670000000";
	cub->weapons[16] = "0000899*1555-*7660000000";
	cub->weapons[17] = "000089+7----**7667000000";
	cub->weapons[18] = "000089++6777688666000000";
	cub->weapons[19] = "000899++++99886677000000";
	cub->weapons[20] = "0008989+++99886677000000";
	cub->weapons[21] = "000898699999888667000000";
	cub->weapons[22] = "000899889998888667000000";
	cub->weapons[23] = "000111286888881113300000";
	cub->weapons[24] = "001221344667712211340000";
	cub->weapons[25] = "012211334554312211134000";
	cub->weapons[26] = "122113344554331333114500";
	cub->weapons[27] = "431133444554343122113450";
	cub->weapons[28] = "122334444554443332234455";
}

void	create_fire(t_cub3d *cub, int i)
{
	cub->weapons = (char **)malloc(sizeof(char *) * 29 + 1);
	cub->weapons[29] = NULL;
	while (cub->weapons[++i])
	{
		cub->weapons[i] = (char *)malloc(sizeof(char) * 24 + 1);
		ft_memset(cub->weapons[i], 0, 24);
	}
	cub->weapons[0] = "0000000000R0000000000000";
	cub->weapons[1] = "0000000000R0000000000000";
	cub->weapons[2] = "000000000RrR000000000000";
	cub->weapons[3] = "000000r00rwr00r000000000";
	cub->weapons[4] = "0000000pppwppp0000000000";
	cub->weapons[5] = "0000000rww#wpr0000000000";
	cub->weapons[6] = "000000Rp#434#pr000000000";
	cub->weapons[7] = "00000Rpw41214wpR00000000";
	cub->weapons[8] = "000000Rr41214rR000000000";
	cub->weapons[9] = "000000011414110000000000";
	complete_fire(cub);
}

void	fire(t_cub3d *cub)
{
	int		j;
	int		i;
	int		end;

	i = 0;
	create_fire(cub, i);
	cub->weapon.row = 29 * cub->weapon.scale.y;
	cub->weapon.len = 24 * cub->weapon.scale.x;
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
