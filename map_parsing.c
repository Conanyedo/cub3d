/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_parsing.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/14 08:33:16 by root              #+#    #+#             */
/*   Updated: 2020/10/17 18:47:21 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void    last_line(t_cub3d *cub)
{
	cub->parse.Y = 0;
	while (cub->map[cub->parse.X][cub->parse.Y])
	{
		if (cub->map[cub->parse.X][cub->parse.Y] != ' ' && cub->map[cub->parse.X][cub->parse.Y] != '1')
            error_msg("ERROR\nLast line invalid");
		cub->parse.Y++;
	}
}

void	map_errors(t_cub3d *cub)
{
	int		i;

	i = -1;
	while (cub->map[--cub->parse.X][0] == '\0')
		cub->map[cub->parse.X] = NULL;
    last_line(cub);
	cub->parse.Y = 0;
	while (++i < cub->parse.X)
	{
		cub->parse.Y = 0;
		if (!cub->map[i][0])
            error_msg_free("ERROR\nEmpty line", cub->map);
		while (cub->map[i][cub->parse.Y])
		{
			if (cub->map[i][cub->parse.Y] == ' ' &&
                cub->map[i + 1][cub->parse.Y] == '0' && cub->parse.Y < (int)ft_strlen(cub->map[i + 1]))
                error_msg_free("ERROR\n0 beneath space", cub->map);
			else if (cub->map[i][cub->parse.Y] == '1')
				cub->parse.Y++;
			else if (cub->map[i][cub->parse.Y] == '0' &&
                (cub->map[i + 1][cub->parse.Y] == ' ' || cub->map[i + 1][cub->parse.Y] == '\0'))
                error_msg_free("ERROR\nSpace or empty line beneath 0", cub->map);
			else
				cub->parse.Y++;
		}
	}
}

void    first_line(t_cub3d *cub)
{
    cub->parse.Y = 0;
    while (cub->map[cub->parse.X][cub->parse.Y])
    {
        if (cub->map[cub->parse.X][cub->parse.Y] != ' ' &&
            cub->map[cub->parse.X][cub->parse.Y] != '1')
            error_msg("ERROR\nFirst line invalid");
        cub->parse.Y++;
    }
}

void    space(t_cub3d *cub)
{
    if (cub->map[cub->parse.X][cub->parse.Y - 1] != ' ' &&
        cub->map[cub->parse.X][cub->parse.Y - 1] != '1')
        error_msg_free("ERROR\nInvalid char before space", cub->map);
    else if (cub->map[cub->parse.X][cub->parse.Y + 1] != ' ' &&
        cub->map[cub->parse.X][cub->parse.Y + 1] != '1' && cub->map[cub->parse.X][cub->parse.Y + 1] != '\0')
            error_msg_free("ERROR\nInvalid char after space", cub->map);
    else if (cub->parse.X - 1 >= 0 && cub->map[cub->parse.X - 1][cub->parse.Y] != ' '
        && cub->map[cub->parse.X - 1][cub->parse.Y] != '1')
    {
        if (cub->parse.Y < (int)ft_strlen(cub->map[cub->parse.X - 1]))
            error_msg_free("ERROR\nInvalid char above space", cub->map);
    }
    cub->parse.Y++;   
}

void    zero(t_cub3d *cub)
{
    if (cub->map[cub->parse.X][cub->parse.Y - 1] == ' ')
        error_msg_free("ERROR\nSpace before 0", cub->map);
    else if (cub->map[cub->parse.X][cub->parse.Y + 1] == ' ')
        error_msg_free("ERROR\nSpace after 0", cub->map);
    else if (cub->map[cub->parse.X][cub->parse.Y + 1] == '\0')
        error_msg_free("ERROR\n0 at the end of the line", cub->map);
    else if (cub->parse.X - 1 >= 0 && cub->map[cub->parse.X - 1][cub->parse.Y] <= 32)
        error_msg_free("ERROR\nSpace or empty line above 0", cub->map);
    cub->parse.Y++;   
}

void	map_checker(t_cub3d *cub)
{
	if (cub->map[cub->parse.X][0] == '0')
		error_msg_free("ERROR\nLine starts with 0", cub->map);
	if (cub->parse.X == 0)
        first_line(cub);
	cub->parse.Y = 1;
	while (cub->map[cub->parse.X][cub->parse.Y])
	{
		if (cub->map[cub->parse.X][cub->parse.Y] == ' ')
            space(cub);
		else if (cub->map[cub->parse.X][cub->parse.Y] == '1' || cub->map[cub->parse.X][cub->parse.Y] == 'N' ||
			cub->map[cub->parse.X][cub->parse.Y] == 'S' || cub->map[cub->parse.X][cub->parse.Y] == 'W' ||
			cub->map[cub->parse.X][cub->parse.Y] == 'E' || cub->map[cub->parse.X][cub->parse.Y] == '2')
			    cub->parse.Y++;
		else if (cub->map[cub->parse.X][cub->parse.Y] == '0')
            zero(cub);
		else if (!cub->map[cub->parse.X][cub->parse.Y])
            error_msg_free("ERROR\nInvalid char in map", cub->map);
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
		if (cub->parse.spawn == 0 && cub->map[cub->parse.X][cub->parse.Y] > 'A')
            spawning(cub);
		else if (cub->map[cub->parse.X][cub->parse.Y] == '2' &&
            !cub->map[cub->parse.X][cub->parse.Y + 1])
            error_msg_free("ERROR\nSprite in an invalid place", cub->map);
		else if (cub->parse.spawn == 1 && cub->map[cub->parse.X][cub->parse.Y] > 'A')
            error_msg_free("ERROR\nSpawning position repeated or in an invalid place", cub->map);
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
	while(i < count)
	{
		tmp[i] = ft_strdup(cub->map[i]);
		i++;
	}
	tmp[i] = ft_strdup(cub->parse.line);
	tmp[i + 1] = NULL;
	return (tmp);
}

void    spawning(t_cub3d *cub)
{
    if (cub->map[cub->parse.X][cub->parse.Y] == 'N' && cub->parse.spawn == 0)
    {
        cub->posX = cub->parse.X;
        cub->posY = cub->parse.Y;
        cub->dirX = -1;
        cub->dirY = 0;
        cub->map[cub->parse.X][cub->parse.Y] = '0';
        cub->parse.spawn = 1;
    }
    else if (cub->map[cub->parse.X][cub->parse.Y] == 'S' && cub->parse.spawn == 0)
    {
        cub->posX = cub->parse.X;
        cub->posY = cub->parse.Y;
        cub->dirX = 1;
        cub->dirY = 0;
        cub->map[cub->parse.X][cub->parse.Y] = '0';
        cub->parse.spawn = 1;
    }
    else if (cub->map[cub->parse.X][cub->parse.Y] == 'E' && cub->parse.spawn == 0)
    {
        cub->posX = cub->parse.X;
        cub->posY = cub->parse.Y;
        cub->dirX = 0;
        cub->dirY = 1;
        cub->map[cub->parse.X][cub->parse.Y] = '0';
        cub->parse.spawn = 1;
    }
    else if (cub->map[cub->parse.X][cub->parse.Y] == 'W' && cub->parse.spawn == 0)
    {
        cub->posX = cub->parse.X;
        cub->posY = cub->parse.Y;
        cub->dirX = 0;
        cub->dirY = -1;
        cub->map[cub->parse.X][cub->parse.Y] = '0';
        cub->parse.spawn = 1;
    }
}