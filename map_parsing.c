/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 08:33:16 by root              #+#    #+#             */
/*   Updated: 2020/11/14 12:35:03 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	map_checker(t_cub3d *cub)
{
	if (cub->map[cub->parse.X][0] == '0')
		error_msg_free("ERROR\nLine starts with 0", cub);
	if (cub->parse.X == 0)
		first_line(cub);
	cub->parse.Y = 1;
	while (cub->map[cub->parse.X][cub->parse.Y])
	{
		if (cub->map[cub->parse.X][cub->parse.Y] == ' ')
			space(cub);
		else if (cub->map[cub->parse.X][cub->parse.Y] == '1' ||
				cub->map[cub->parse.X][cub->parse.Y] == 'N' ||
				cub->map[cub->parse.X][cub->parse.Y] == 'S' ||
				cub->map[cub->parse.X][cub->parse.Y] == 'W' ||
				cub->map[cub->parse.X][cub->parse.Y] == 'E' ||
				cub->map[cub->parse.X][cub->parse.Y] == '2')
			cub->parse.Y++;
		else if (cub->map[cub->parse.X][cub->parse.Y] == '0')
			zero(cub);
		else if (!cub->map[cub->parse.X][cub->parse.Y])
			error_msg_free("ERROR\nInvalid char in map", cub);
		else
			cub->parse.Y++;
	}
	printf("%s\n", cub->map[cub->parse.X]);
}

void	map(t_cub3d *cub)
{
	if (cub->parse.mapline == 0)
	{
		cub->map = (char**)malloc(2 * sizeof(char*));
		cub->map[1] = NULL;
		cub->map[cub->parse.X] = cub->parse.line;
		cub->parse.mapline = 1;
	}
	else
		cub->map = push(cub);
	map_checker(cub);
	cub->parse.Y = 0;
	while (cub->map[cub->parse.X][cub->parse.Y])
	{
		if (cub->parse.spawn == 0 && character(cub) == 1)
			spawning(cub);
		else if (cub->map[cub->parse.X][cub->parse.Y] == '2' &&
				!cub->map[cub->parse.X][cub->parse.Y + 1])
			error_msg_free("ERROR\nSprite in an invalid place", cub);
		else if (cub->map[cub->parse.X][cub->parse.Y] == '2')
			cub->spriteNum++;
		else if (cub->parse.spawn == 1 && character(cub) == 1)
			error_msg_free("ERROR\nSpawning position repeated or invalid", cub);
		else if (character(cub) == 0)
			error_msg_free("ERROR\nInvalid char in the map", cub);
		cub->parse.Y++;
	}
	cub->parse.X++;
}

char	**push(t_cub3d *cub)
{
	char	**tmp;
	int		count;
	int		i;

	i = 0;
	count = 0;
	while (cub->map[count])
		count++;
	tmp = malloc((count + 2) * sizeof(char*));
	while (i < count)
	{
		tmp[i] = ft_strdup(cub->map[i]);
		i++;
	}
	tmp[i] = ft_strdup(cub->parse.line);
	tmp[i + 1] = NULL;
	return (tmp);
}

void	spawning(t_cub3d *cub)
{
	if (!cub->map[cub->parse.X][cub->parse.Y + 1] ||
			cub->map[cub->parse.X - 1][cub->parse.Y] == ' ' ||
			cub->map[cub->parse.X - 1][cub->parse.Y] == '\0')
		error_msg_free("ERROR\nSpawning position in an invalid place", cub);
	if (cub->map[cub->parse.X][cub->parse.Y] == 'N' ||
			cub->map[cub->parse.X][cub->parse.Y] == 'S')
		spawning_ns(cub);
	else if (cub->map[cub->parse.X][cub->parse.Y] == 'E')
	{
		cub->posX = cub->parse.X;
		cub->posY = cub->parse.Y;
		cub->dirX = 0;
		cub->dirY = 1;
		cub->planeX = 0.66;
		cub->planeY = 0;
		cub->parse.spawn = 1;
		cub->map[cub->parse.X][cub->parse.Y] = '0';
	}
	else if (cub->map[cub->parse.X][cub->parse.Y] == 'W')
	{
		cub->posX = cub->parse.X;
		cub->posY = cub->parse.Y;
		cub->dirX = 0;
		cub->dirY = -1;
		cub->planeX = -0.66;
		cub->planeY = 0;
		cub->parse.spawn = 1;
		cub->map[cub->parse.X][cub->parse.Y] = '0';
	}
}

void	spawning_ns(t_cub3d *cub)
{
	if (cub->map[cub->parse.X][cub->parse.Y] == 'N')
	{
		cub->posX = cub->parse.X;
		cub->posY = cub->parse.Y;
		cub->dirX = -1;
		cub->dirY = 0;
		cub->planeX = 0;
		cub->planeY = 0.66;
		cub->parse.spawn = 1;
		cub->map[cub->parse.X][cub->parse.Y] = '0';
	}
	else if (cub->map[cub->parse.X][cub->parse.Y] == 'S')
	{
		cub->posX = cub->parse.X;
		cub->posY = cub->parse.Y;
		cub->dirX = 1;
		cub->dirY = 0;
		cub->planeX = 0;
		cub->planeY = -0.66;
		cub->parse.spawn = 1;
		cub->map[cub->parse.X][cub->parse.Y] = '0';
	}
}

int		character(t_cub3d *cub)
{
	int	found;

	found = 0;
	if (cub->map[cub->parse.X][cub->parse.Y] == 'N' ||
			cub->map[cub->parse.X][cub->parse.Y] == 'S' ||
			cub->map[cub->parse.X][cub->parse.Y] == 'W' ||
			cub->map[cub->parse.X][cub->parse.Y] == 'E')
		found = 1;
	else if (!cub->map[cub->parse.X][cub->parse.Y] ||
			cub->map[cub->parse.X][cub->parse.Y] == '0' ||
			cub->map[cub->parse.X][cub->parse.Y] == ' ' ||
			cub->map[cub->parse.X][cub->parse.Y] == '1')
		found = 2;
	return (found);
}
