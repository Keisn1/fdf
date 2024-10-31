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
				add_back_point(&ret, (t_point){idx, idx + 1});
			if (count_m < wf_m)
				add_back_point(&ret, (t_point){idx, idx + wf_n});
			count_n++;
			idx++;
		}
	}
	return (ret);
}

void	wf_to_img(t_mlx_data mlx_data, t_img img, t_mat M, t_list *wf)
{
	t_point	*idx;
	t_list	*line;
	t_list	*head;

	while (wf)
	{
		idx = (t_point *)(wf->content);
		line = get_bres_line((t_point){
				(int)round(M.mat[0][idx->i]) + (img.width / 2),
				(int)round(M.mat[1][idx->i]) + (img.height / 2)
			},
			(t_point){
				(int)round(M.mat[0][idx->j]) + (img.width / 2),
				(int)round(M.mat[1][idx->j]) + (img.height / 2)
			} );
		head = line;
		while (head)
		{
			img_put_pixel(mlx_data.mlx_ptr, &img, *(t_point *)head->content,
				0xFF00FF);
			head = head->next;
		}
		ft_lstclear(&line, free);
		wf = wf->next;
	}
}
