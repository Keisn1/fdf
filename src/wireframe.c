/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wireframe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 13:14/35 by kfreyer           #+#    #+#             */
/*   Updated: 2024/10/29 13:14:35 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "bresenham.h"
#include "fdf.h"
#include "libft.h"
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

t_list	*get_wireframe_indices(size_t wf_m, size_t wf_n)
{
	t_list	*ret;
	size_t	count_m;
	size_t	count_n;
	size_t	idx;

	ret = NULL;
	count_m = 0;
	idx = 0;
	while (count_m < wf_m)
	{
		count_m++;
		count_n = 0;
		while (count_n < wf_n)
		{
			if (count_n < wf_n - 1)
				add_back_point(&ret, (t_pixel){idx, idx + 1});
			if (count_m < wf_m)
				add_back_point(&ret, (t_pixel){idx, idx + wf_n});
			count_n++;
			idx++;
		}
	}
	if (idx) {

	}
	return (ret);
}

void	wf_to_img(t_mlx_data mlx_data, t_img img, t_matrix M, t_map map)
{
	t_list	*line;
	t_list	*head;


	unsigned int	count_m;
	unsigned int	count_n;
	size_t idx;

	count_m = 0;
	idx = 0;
	while (count_m < map.map.m) {
		count_n = 0;
		while (count_n < map.map.n) {
			if (count_n < map.map.n -1) {
				line = get_bres_line((t_pixel){
						(int)round(M.mat[0][idx]),
						(int)round(M.mat[1][idx])
					},
					(t_pixel){
						(int)round(M.mat[0][idx+1]),
						(int)round(M.mat[1][idx+1])
					} );

				head = line;
				while (head)
				{
					img_put_pixel(mlx_data.mlx_ptr, &img, *(t_pixel *)head->content,
								  0xFF00FF);
					head = head->next;
				}
				ft_lstclear(&line, free);
			}
			if (count_m < map.map.m-1) {
				line = get_bres_line((t_pixel){
						(int)round(M.mat[0][idx]),
						(int)round(M.mat[1][idx])
					},
					(t_pixel){
						(int)round(M.mat[0][idx+map.map.n]),
						(int)round(M.mat[1][idx+map.map.n])
					} );

				head = line;
				while (head)
				{
					img_put_pixel(mlx_data.mlx_ptr, &img, *(t_pixel *)head->content,
								  0xFF00FF);
					head = head->next;
				}
				ft_lstclear(&line, free);
			}
			count_n++;
			idx++;
		}
		count_m++;
	}
}
