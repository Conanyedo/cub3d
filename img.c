/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   img.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ybouddou <ybouddou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/03/09 23:42:36 by ybouddou          #+#    #+#             */
/*   Updated: 2020/03/12 15:53:38 by ybouddou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mlx.h"

int     main()
{
    char	*mlx_ptr;
    char	*mlx_win;
    void	*img_ptr;
    int		*img_data;
    int     bpp;
    int     size_line;
    int     endian;
    // int		count_w ;
    // int		count_h = -1;
    
    mlx_ptr = mlx_init();
    mlx_win = mlx_new_window(mlx_ptr, 1000, 500, "image");
    img_ptr = mlx_new_image(mlx_ptr, 800, 600);
    img_data = (int *)mlx_get_data_addr(img_ptr, &bpp, &size_line, &endian);
    img_data[6401] = 255;
    img_data[1515] = 0x007C00;
    // while (++count_h < 360)
    // {
    //     count_w = -1;
    //     while (++count_w < 640)
    //     {
    //         if (count_w % 2)
    //             img_data[count_h * 640 + count_w] = 0x007C00;
    //         else	
    //             img_data[count_h * 640 + count_w] = 0xB20000;
    //     }
    // }
    mlx_put_image_to_window(mlx_ptr, mlx_win, img_ptr, 0, 0);
    mlx_loop(mlx_ptr);
}