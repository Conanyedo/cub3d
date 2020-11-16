/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:47:27 by ybouddou          #+#    #+#             */
/*   Updated: 2020/11/16 10:01:00 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "mlx.h"
# include "Utils/utils.h"
# include <math.h>
# include <fcntl.h>
# include <stdio.h>

typedef struct	s_resolution
{
	int		h;
	int		w;
}				t_res;

typedef struct	s_mlx
{
	void	*p;
	void	*w;
}				t_mlx;

typedef	struct	s_fd
{
	int		lines;
	int		NO;
	int		SO;
	int		WE;
	int		EA;
	int		S;
}				t_fd;

typedef struct	s_repetition
{
	int		res;
	int		NO;
	int		SO;
	int		WE;
	int		EA;
	int		S;
	int		F;
	int		C;
}				t_rep;

typedef struct	s_path
{
	char	*NO;
	char	*SO;
	char	*WE;
	char	*EA;
	char	*S;
}				t_path;

typedef struct	s_parse
{
	int		r;
	int		mapline;
	char	*line;
	char	**splitted;
	char	**colors;
	int		X;
	int		Y;
	int		spawn;
	int		rgb;
}				t_parse;

typedef struct	s_img
{
	void	*img_ptr;
	int		*img_data;
	int		bpp;
	int		size_line;
	int		endian;
	int		w;
	int		h;
}				t_img;

typedef struct	s_rgb
{
	int		r;
	int		g;
	int		b;
}				t_rgb;

typedef struct	s_sprite
{
	double	x;
	double	y;
	double	dist;
	int		order;
}				t_sprite;

typedef struct	s_cub3d
{
	t_res		res;
	t_rep		rep;
	t_mlx		mlx;
	t_path		path;
	t_rgb		F;
	t_rgb		C;
	t_parse		parse;
	t_img		img;
	t_fd		fd;
	t_img		txt[5];
	t_sprite	*sprite;
	
	unsigned char		*image;
	int			save;
	int			color;
	int			bmp_pos;
	
	int			keyboard[300];
	char		**map;
	int			ray;
	int			mapX;
	int			mapY;
	double		posX;
	double		posY;
	double		dirX;
	double		dirY;
	double		planeX;
	double		planeY;
	double		oldDirX;
	double		oldPlaneX;
	double		rotateSpeed;
	double		moveSpeed;
	double		cameraX;
	double		rayDirX;
	double		rayDirY;
	double		sidedistX;
	double		sidedistY;
	double		deltaDistX;
	double		deltaDistY;
	double		perpWallDist;
	int			stepX;
	int			stepY;
	int			hit;
	int			side;
	int			lineHeight;
	int			drawStart;
	int			drawEnd;
	int			texWidth;
	int			texHeight;
	double		wallX;
	int			texX;
	int			texY;
	double		step;
	double		texPos;

	int			spriteNum;
	int			spriteN;
	double		*ZBuffer;
	double		spriteX;
	double		spriteY;
	double		invDet;
	double		transformX;
	double		transformY;
	int			spriteScreenX;
	int			spriteHeight;
	int			spriteWidth;
	int			drawStartY;
	int			drawStartX;
	int			drawEndY;
	int			drawEndX;
	int			spriteLine;
	int			d;
}				t_cub3d;

void			init(t_cub3d *cub);
void			ft_free(char **arr);
void			checker(char **s, t_cub3d *cub);
void			range(t_rgb *rgb, t_cub3d *cub);
int				key_pressed(int key, t_cub3d *cub);
int				key_released(int key, t_cub3d *cub);
int				key_close(t_cub3d *cub);
unsigned long	create_rgb(t_rgb *rgb);
void			resolution(t_cub3d *cub);
void			identifier(t_cub3d *cub);
void			fc(t_cub3d *cub);
void			sprit(t_cub3d *cub);
void			map(t_cub3d *cub);
void			map_checker(t_cub3d *cub);
void			map_errors(t_cub3d *cub);
char			**push(t_cub3d *cub);
void			exist(t_cub3d *cub);
void			error_msg_free(char *s, t_cub3d *cub);
void			error_free(char *s, t_cub3d *cub, char **tofree);
void			error_msg(char *s);
void			fc_color(t_rgb *fc, t_parse *parse, int *rep, t_cub3d *cub);
void			fc_checker(t_parse *parse, t_cub3d *cub);
void			path(char **path, t_cub3d *cub, int *fd, int *rep);
void			first_line(t_cub3d *cub);
void			space(t_cub3d *cub);
void			zero(t_cub3d *cub);
void			last_line(t_cub3d *cub);
void			spawning(t_cub3d *cub);
void			spawning_ns(t_cub3d *cub);
int				character(t_cub3d *cub);
void			moves_up_down(t_cub3d *cub);
void			movesides(t_cub3d *cub);
void			look(t_cub3d *cub);
void			calc(t_cub3d *cub);
void			sidedist(t_cub3d *cub);
void			hit(t_cub3d *cub);
void			wall(t_cub3d *cub);
void			rendering(t_cub3d *cub);
void			wallrendering(t_cub3d *cub);
void			spriteposition(t_cub3d *cub, int x);
void			spritedistance(t_cub3d *cub);
void			spritesort(t_cub3d *cub);
void			sprite(t_cub3d *cub);
void			spriterendering(t_cub3d *cub);
void			bmp(t_cub3d *cub, int ac, char **av);
void			bmp_save(t_cub3d *cub);
void			bmp_filling(t_cub3d *cub, t_rgb *fc);

#endif
