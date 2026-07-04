/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_mlx.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ffrattar <ffrattar@student.42firenze.it    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/24 02:18:02 by kel               #+#    #+#             */
/*   Updated: 2026/05/07 15:52:25 by ffrattar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3D.h"

static void	destroy_each_tex(t_cub *cub, t_textid idx)
{
	if (cub->assets.img[idx].img)
		mlx_destroy_image(cub->mlx, cub->assets.img[idx].img);
	cub->assets.img[idx].img = NULL;
	cub->assets.img[idx].addr = NULL;
	cub->assets.img[idx].w = 0;
	cub->assets.img[idx].h = 0;
	cub->assets.img[idx].bpp = 0;
	cub->assets.img[idx].line_len = 0;
	cub->assets.img[idx].endian = 0;
}

static int	init_each_texture(t_cub *cub, t_textid idx)
{
	int	w;
	int	h;

	cub->assets.img[idx].img = mlx_xpm_file_to_image(cub->mlx,
			cub->assets.path[idx], &w, &h);
	if (!cub->assets.img[idx].img)
		return (E_TEX_IMG);
	cub->assets.img[idx].w = w;
	cub->assets.img[idx].h = h;
	cub->assets.img[idx].addr = mlx_get_data_addr(cub->assets.img[idx].img,
			&cub->assets.img[idx].bpp, &cub->assets.img[idx].line_len,
			&cub->assets.img[idx].endian);
	if (!cub->assets.img[idx].addr)
	{
		ft_putstr_fd("Texture: ", 2);
		ft_putstr_fd(cub->assets.path[idx], 2);
		destroy_each_tex(cub, idx);
		return (E_TEX_ADDR);
	}
	return (OK);
}

static int	load_textures(t_cub *cub)
{
	int	i;
	int	j;
	int	code;

	i = 0;
	while (i < T_COUNT)
	{
		code = init_each_texture(cub, i);
		if (code != OK)
		{
			j = 0;
			while (j < i)
			{
				destroy_each_tex(cub, j);
				j++;
			}
			return (code);
		}
		i++;
	}
	return (OK);
}

int	init_mlx(t_cub *cub)
{
	int	code;

	cub->mlx = mlx_init();
	if (!cub->mlx)
		return (E_MLX_PTR);
	cub->win = mlx_new_window(cub->mlx, WIN_WIDTH, WIN_HEIGHT, "CUB3D");
	if (!cub->win)
		return (E_WIN_PTR);
	cub->frame.img = mlx_new_image(cub->mlx, WIN_WIDTH, WIN_HEIGHT);
	if (!cub->frame.img)
		return (E_IMG_PTR);
	cub->frame.addr = mlx_get_data_addr(cub->frame.img, &cub->frame.bpp,
			&cub->frame.line_len, &cub->frame.endian);
	if (!cub->frame.addr)
		return (E_ADDR_PTR);
	code = load_textures(cub);
	if (code != OK)
		return (code);
	return (OK);
}
