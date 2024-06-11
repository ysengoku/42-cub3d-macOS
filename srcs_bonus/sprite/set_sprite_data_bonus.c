/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_sprite_data_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yusengok <yusengok@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/10 13:45:40 by yusengok          #+#    #+#             */
/*   Updated: 2024/06/10 14:13:32 by yusengok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

/*
static void	get_sprite_count(t_cub3d *data)
{
	int	x;
	int	y;
	int	i;

	y = -1;
	i = 0;
	data->sprite_count = 0;
	while (++y < data->map.map_len_y)
	{
		x = -1;
		while (data->map.map[y][++x])
		{
			if (data->map.map[y][x] == '2')
				data->sprite_count++;
		}
	}
}

void	store_sprites(t_cub3d *data)
{
	int	x;
	int	y;
	int	i;

	i = 0;
	get_sprite_count(data);
	data->sprites = ft_calloc(sizeof(t_sprite), data->sprite_count + 1);
	if (!data->sprites)
	{
		free_all(data, 1);
		ft_perror_exit("malloc", 1);
	}
	y = 0;
	while (i < data->sprite_count)
	{
		x = -1;
		while (data->map.map[y][++x])
		{
			if (data->map.map[y][x] == '2')
			{
				data->sprites[i].map_x = (double)x + 0.5;
				data->sprites[i].map_y = (double)y + 0.5;
				i++;
			}
		}
		y++;
	}
}

void	set_sprite_data(t_cub3d *data, t_sprite *sprites)
{
	double	inverse_matrix_factor;
	int		i;

	i = 0;
	// 行列の決定因子（行列の操作を元に戻すために必要な値）の逆数を計算
	inverse_matrix_factor = 1.0 / (data->player.plane_x * data->player.dir_y
		- data->player.dir_x * data->player.plane_y);

	while (i < data->sprite_count)
	{
		//=== プレイヤーの位置に対するスプライトの相対位置を計算 ===
		sprites[i].relative_x = sprites[i].map_x - data->player.pos_x;
		sprites[i].relative_y = sprites[i].map_y - data->player.pos_y;

		//=== プレイヤーの視野（カメラ平面）とスプライトとの位置との関係を計算 ===
		// 逆行列を使ってスプライトの位置をカメラ平面に投影
		// スプライトがプレイヤーの視野の中心から左右どちらにどれだけ離れているかを計算
		sprites[i].camera_x = inverse_matrix_factor * (data->player.dir_y
			* sprites[i].relative_x - data->player.dir_x * sprites[i].relative_y);
		// プレイヤーからスプライトまでの距離を計算
		sprites[i].camera_y = inverse_matrix_factor * (-data->player.plane_y
			* sprites[i].relative_x + data->player.plane_x * sprites[i].relative_y);

		// スプライトが画面のどのx座標に表示されるべきかを計算
		// スプライトのカメラ相対座標xをスプライトのカメラ相対座標yで割ることで、スプライトがカメラから見てどの方向にどれだけ離れているかを計算し、その値を画面の中心（WIN_W / 2）に加えることでスプライトが画面のどのx座標に表示されるべきかを計算する。
		sprites[i].screen_x = (int)((WIN_W / 2) * (1 + sprites[i].camera_x
			/ sprites[i].camera_y));
		// スプライトが画面上でどれだけの高さを占めるか計算
		// ウィンドウの高さをスプライトまでの距離で割る。
		sprites[i].draw_height = ft_abs((int)(WIN_H / sprites[i].camera_y));
		// スプライトが画面上でどれだけの幅を占めるか計算
		sprites[i].draw_width = sprites[i].draw_height;
		// スプライトが画面上でどのx座標からどのx座標まで表示されるべきかを計算
		sprites[i].start_x = -sprites[i].draw_width / 2 + sprites[i].screen_x;
		if (sprites[i].start_x < 0)
		sprites[i].start_x = 0;
		sprites[i].end_x = sprites[i].draw_width / 2 + sprites[i].screen_x;
		if (sprites[i].end_x >= WIN_W)
			sprites[i].end_x = WIN_W - 1;
		// スプライトが画面上でどのy座標からどのy座標まで表示されるべきかを計算
		sprites[i].start_y = -sprites[i].draw_height / 2 + WIN_H / 2;
		if (sprites[i].start_y < 0)
			sprites[i].start_y = 0;
		sprites[i].end_y = sprites[i].draw_height / 2 + WIN_H / 2;
		if (sprites[i].end_y >= WIN_H)
			sprites[i].end_y = WIN_H - 1;
		i++;
	}
}
*/