/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/07 14:47:27 by ybouddou          #+#    #+#             */
/*   Updated: 2020/03/13 19:28:59 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


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
    char	*line;
	char	**splitted;
	char	**colors;
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

typedef struct		s_cub3d
{
    t_res   res;
    t_mlx   mlx;
    t_path  path;
    t_rgb   F;
    t_rgb   C;
    t_parse parse;
    t_img   img;

    int     keyboard[300];
    
    int     mapWidth;
    int     mapHeight;
    int     ray;
    int     mapX;
	int     mapY;
    int     **worldMap;
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
    int     change;
    int     look;
    t_img   txt[5];
}					t_cub3d;

void	init(t_cub3d *cub);
void    ft_free(char **arr);
void	checker(char **s);
void	range(t_rgb *cub);
int		key_pressed(int key, t_cub3d *cub);
int		key_released(int key, t_cub3d *cub);
unsigned long createRGB(t_rgb *rgb);
