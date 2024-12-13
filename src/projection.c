/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/13 18:38/58 by kfreyer           #+#    #+#             */
/*   Updated: 2024/12/13 18:38:58 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_matrix	get_isometric_projection(t_map map)
{
	t_matrix	vectors;
	t_matrix	rot_matrix;
	t_matrix	isometric_projection;

	vectors = map_to_vectors(map);
	rot_matrix = get_rot_matrix();
	isometric_projection = mat_mul(rot_matrix, vectors);
	free_matrix(vectors);
	free_matrix(rot_matrix);
	return (isometric_projection);
}
