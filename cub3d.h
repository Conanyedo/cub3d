/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:47:27 by ybouddou          #+#    #+#             */
/*   Updated: 2020/10/31 14:48:45 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"
#include "mlx/mlx_png.h"
#include <math.h>
#include "gnl/get_next_line.h"
#include "Libft/libft.h"
#include <fcntl.h>
#include <stdio.h>

typedef struct  s_resolution
{
    int h;
    int w;
}               t_res;

typedef struct  s_mlx
{
    void    *p;
    void    *w;
}               t_mlx;

typedef struct  s_fd
{
    int lines;
    int NO;
    int SO;
    int WE;
    int EA;
    int S;
}               t_fd;

typedef struct  s_repetition
{
    int res;
    int NO;
    int SO;
    int WE;
    int EA;
    int S;
    int F;
    int C;
}               t_rep;

typedef struct  s_path
{
    char    *NO;
    char    *SO;
    char    *WE;
    char    *EA;
    char    *S;
}               t_path;

typedef struct  s_parse
{
	int		r;
    int     mapline;
    char	*line;
	char	**splitted;
	char	**colors;
    int     nline;
    int     X;
    int     Y;
    int     spawn;
    int     rgb;
}               t_parse;

typedef struct  s_img
{
    void	*img_ptr;
    int		*img_data;
    int     bpp;
    int     size_line;
    int     endian;
    int     w;
    int     h;
}               t_img;

typedef struct  s_rgb
{
    int r;
    int g;
    int b;
}               t_rgb;

typedef struct  s_sprite
{
    double  x;
    double  y;
}               t_sprite;


typedef struct		s_cub3d
{
    t_res   res;
    t_rep   rep;
    t_mlx   mlx;
    t_path  path;
    t_rgb   F;
    t_rgb   C;
    t_parse parse;
    t_img   img;
    t_fd    fd;
    t_img   txt[5];
    t_sprite    *sprite;
    
    int     keyboard[300];
    
    char    **map;

    int     ray;
    int     mapX;
	int     mapY;
    double  posX;
    double  posY;
    double  dirX;
    double  dirY;
    double  planeX;
    double  planeY;
    double  oldDirX;
	double  oldPlaneX;
    double  rotateSpeed;
    double  moveSpeed;
    double  cameraX;
	double  rayDirX;
	double  rayDirY;
	double  sideDistX;
	double  sideDistY;
	double  deltaDistX;
	double  deltaDistY;
	double  perpWallDist;
	int     stepX;
	int     stepY;
	int     hit;
	int     side;
    int     lineHeight;
	int     drawStart;
    int     drawEnd;
    int     texWidth;
    int     texHeight;
    double  wallX;
    int     texX;
    int     texY;
    double  step;
    double  texPos;
    //sprite
    int     spriteNum;
    int     spriteN;
    int     spritePos;
    double  *ZBuffer;
    int     *spriteOrder;
    double  *spriteDist;
    double  spriteX;
    double  spriteY;
    double  invDet;
    double  transformX;
    double  transformY;
    int     spriteScreenX;
    int     spriteHeight;
    int     spriteWidth;
    int     drawStartY;
    int     drawStartX;
    int     drawEndY;
    int     drawEndX;
    int     spriteStripe;
    int     spriteLine;
    int     d;
}					t_cub3d;

void	init(t_cub3d *cub);
void    ft_free(char **arr);
void	freeAll(t_cub3d *cub);
void	checker(char **s);
void	range(t_rgb *cub);
int		key_pressed(int key, t_cub3d *cub);
int		key_released(int key, t_cub3d *cub);
unsigned long createRGB(t_rgb *rgb);
void	resolution(t_cub3d *cub);
void	identifier(t_cub3d *cub);
void	FC(t_cub3d *cub);
void	sprit(t_cub3d *cub);
void	map(t_cub3d *cub);
void	map_checker(t_cub3d *cub);
void	map_errors(t_cub3d *cub);
char	**push(t_cub3d *cub);
void    exist(t_cub3d *cub);
void    error_msg_free(char *s, char **tofree);
void    error_msg(char *s);
void	FC_checker(t_rgb *FC, t_parse *parse, int *rep);
void	path(char **path, t_parse *parse, int *fd, int *rep);
void    first_line(t_cub3d *cub);
void    space(t_cub3d *cub);
void    zero(t_cub3d *cub);
void    last_line(t_cub3d *cub);
void    spawning(t_cub3d *cub);
void    spawningNS(t_cub3d *cub);
void    sprite(t_cub3d *cub, int x);
void    spriteInit(t_cub3d *cub);
void	movesUpDown(t_cub3d *cub);
void    moveSides(t_cub3d *cub);
void	look(t_cub3d *cub);
void	calc(t_cub3d *cub);
void	sideDist(t_cub3d *cub);
void	hit(t_cub3d *cub);
void	wall(t_cub3d *cub);
void	render(t_cub3d *cub);
void	spriteRender(t_cub3d *cub);
int     character(t_cub3d *cub);
void	spriteSort(t_cub3d *cub);
void	swap(double *i, double *j);