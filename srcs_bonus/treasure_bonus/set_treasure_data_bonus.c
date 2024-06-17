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

static void	calculate_camera_coordinates(t_cub3d *data, t_treasure *treasure);
static void	get_draw_range(t_cub3d *data, t_treasure *treasure);

void	store_sprite_coordinates(t_cub3d *data)
{
	int	x;
	int	y;

	y = 0;
	while (data->map.map[y])
	{
		x = 0;
		while(data->map.map[y][x])
		{
			if (data->map.map[y][x] == 'T')
			{
				data->treasure.map.x = (double)x + 0.5;
				data->treasure.map.y = (double)y + 0.5;
			}
			x++;
		}
		y++;
	}
}

void	set_treasure_data(t_cub3d *data, t_treasure *treasure)
{
	calculate_camera_coordinates(data, treasure);
	if (treasure->camera.y > 0 && fabs(treasure->camera.x
			/ treasure->camera.y) < data->player.plane_length)
	{
		get_draw_range(data, treasure);
		treasure->visible = 1;
	}
}

static void	calculate_camera_coordinates(t_cub3d *data, t_treasure *treasure)
{
	double	inverse_matrix_factor;
		
	inverse_matrix_factor = 1.0 / (data->player.plane.x * data->player.dir.y
		- data->player.dir.x * data->player.plane.y);
	treasure->relative_pos.x = treasure->map.x - data->player.pos.x;
	treasure->relative_pos.y = treasure->map.y - data->player.pos.y;
	treasure->camera.x = inverse_matrix_factor
		* (data->player.dir.y * treasure->relative_pos.x
		- data->player.dir.x * treasure->relative_pos.y);
	treasure->camera.y = inverse_matrix_factor
		* (-data->player.plane.y * treasure->relative_pos.x
		+ data->player.plane.x * treasure->relative_pos.y);
	data->treasure.visible = 0;
}

static void	get_draw_range(t_cub3d *data, t_treasure *treasure)
{
	treasure->screen_x = (int)(data->win_half_w 
		* (1 + treasure->camera.x / treasure->camera.y));
	treasure->draw_height = ft_abs((int)(WIN_H / treasure->camera.y));
	treasure->start_y = -treasure->draw_height / 2 + WIN_H / 2;
	if (treasure->start_y < 0)
		treasure->start_y = 0;
	treasure->end_y = treasure->draw_height / 2 + WIN_H / 2;
	if (treasure->end_y >= WIN_H)
			treasure->end_y = WIN_H - 1;
	treasure->draw_width = treasure->draw_height;
	treasure->start_x = -treasure->draw_width / 2 + treasure->screen_x;
	if (treasure->start_x < 0)
		treasure->start_x = 0;
	treasure->end_x = treasure->draw_width / 2 + treasure->screen_x;
	if (treasure->end_x >= WIN_W)
		treasure->end_x = WIN_W - 1;
}


/*
void	set_sprite_data(t_cub3d *data, t_sprite *treasure)
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
		treasure[i].relative_x = treasure[i].map_x - data->player.pos_x;
		treasure[i].relative_y = treasure[i].map_y - data->player.pos_y;

		//=== プレイヤーの視野（カメラ平面）とスプライトとの位置との関係を計算 ===
		// 逆行列を使ってスプライトの位置をカメラ平面に投影
		// スプライトがプレイヤーの視野の中心から左右どちらにどれだけ離れているかを計算
		treasure[i].camera_x = inverse_matrix_factor * (data->player.dir_y
			* treasure[i].relative_x - data->player.dir_x * treasure[i].relative_y);
		// プレイヤーからスプライトまでの距離を計算
		treasure[i].camera_y = inverse_matrix_factor * (-data->player.plane_y
			* treasure[i].relative_x + data->player.plane_x * treasure[i].relative_y);

		// スプライトが画面のどのx座標に表示されるべきかを計算
		// スプライトのカメラ相対座標xをスプライトのカメラ相対座標yで割ることで、スプライトがカメラから見てどの方向にどれだけ離れているかを計算し、その値を画面の中心（WIN_W / 2）に加えることでスプライトが画面のどのx座標に表示されるべきかを計算する。
		treasure[i].screen_x = (int)((WIN_W / 2) * (1 + treasure[i].camera_x
			/ treasure[i].camera_y));
		// スプライトが画面上でどれだけの高さを占めるか計算
		// ウィンドウの高さをスプライトまでの距離で割る。
		treasure[i].draw_height = ft_abs((int)(WIN_H / treasure[i].camera_y));
		// スプライトが画面上でどれだけの幅を占めるか計算
		treasure[i].draw_width = treasure[i].draw_height;
		// スプライトが画面上でどのx座標からどのx座標まで表示されるべきかを計算
		treasure[i].start_x = -treasure[i].draw_width / 2 + treasure[i].screen_x;
		if (treasure[i].start_x < 0)
		treasure[i].start_x = 0;
		treasure[i].end_x = treasure[i].draw_width / 2 + treasure[i].screen_x;
		if (treasure[i].end_x >= WIN_W)
			treasure[i].end_x = WIN_W - 1;
		// スプライトが画面上でどのy座標からどのy座標まで表示されるべきかを計算
		treasure[i].start_y = -treasure[i].draw_height / 2 + WIN_H / 2;
		if (treasure[i].start_y < 0)
			treasure[i].start_y = 0;
		treasure[i].end_y = treasure[i].draw_height / 2 + WIN_H / 2;
		if (treasure[i].end_y >= WIN_H)
			treasure[i].end_y = WIN_H - 1;
		i++;
	}
}
*/