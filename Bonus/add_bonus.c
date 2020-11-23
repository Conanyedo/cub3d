/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_bonus.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/21 13:32:21 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/23 18:37:20 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d_bonus.h"

void	bonus(t_cub3d *cub)
{
	if (cub->mini.show)
		minimap(cub);
	life_bar(cub);
	if (cub->weapon.fire)
		fire(cub);
	else
		weapon(cub);
	bullets(cub);
}

void	fire_bullets(t_cub3d *cub)
{
	if (cub->keyboard[49])
	{
		if (cub->bullet.bullets > 0)
		{
			cub->weapon.fire = 1;
			system("afplay texture/gunshot.mp3 &>/dev/null&");
			cub->bullet.bullets--;
		}
		cub->keyboard[49] = 0;
	}
	if (cub->keyboard[15])
	{
		cub->bullet.bullets = 5;
		cub->keyboard[15] = 0;
	}
}

void	bonus_keys(t_cub3d *cub)
{
	cub->weapon.fire = 0;
	if (cub->keyboard[46])
	{
		cub->mini.show = cub->mini.show == 1 ? 0 : 1;
		cub->keyboard[46] = 0;
	}
	fire_bullets(cub);
	if (cub->life.hearts == 0)
	{
		ft_putstr_fd("GAME OVER\n", 2);
		key_close(cub);
	}
}
