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
#include "matrix.h"
#include <math.h>

void	norm_vectors(t_matrix *mat)
{
	double	max_norm;
	double	norm;
	size_t	c1;

	max_norm = 0;
	norm = 0;
	c1 = 0;
	while (c1 < mat->n)
	{
		norm = sqrt(pow(mat->mat[0][c1], 2) + pow(mat->mat[1][c1], 2)
				+ pow(mat->mat[1][c1], 2));
		if (norm > max_norm)
			max_norm = norm;
		c1++;
	}
	scale_matrix(mat, 1 / max_norm);
}

double	get_init_scale(t_matrix projection, double width, double height)
{
	t_extrema	e;
	double		max_y;
	double		max_x;
	double		init_scale;

	e = get_extrema(projection);
	max_x = ft_abs_double(e.max_x);
	if (ft_abs_double(e.min_x) > max_x)
		max_x = ft_abs_double(e.min_x);
	max_y = ft_abs_double(e.max_y);
	if (ft_abs_double(e.min_y) > max_y)
		max_y = ft_abs_double(e.min_y);
	init_scale = width / 2.2 / max_x;
	if (height / 2.2 / max_y < init_scale)
		init_scale = height / 2.2 / max_y;
	return (init_scale);
}

t_projection	new_projection(char *filename, double width, double height)
{
	t_projection	p;
	t_map			map;

	map = parse_map(filename);
	p.drehwinkel = 2;
	p.zoom_factor = 1.02;
	p.zoom = 0;
	p.rotation = 0;
	p.translation_h = 0;
	p.translation_v = 0;
	p.last_pos_x = 0;
	p.last_pos_y = 0;
	p.rows = map.map.m;
	p.cols = map.map.n;
	p.vectors = map_to_vectors(map);
	norm_vectors(&p.vectors);
	p.kind = ISOMETRIC;
	p.projection = get_isometric_projection(p.vectors);
	p.colors = map.colors;
	p.init_scale = get_init_scale(p.projection, width, height);
	scale_matrix(&p.projection, p.init_scale);
	free_matrix(map.map);
	return (p);
}

void	rebuild_projection(t_projection *p)
{
	t_matrix	rotation_z;
	t_matrix	rotated_vectors;

	rotation_z = get_rot_matrix_z(p->rotation * p->drehwinkel);
	rotated_vectors = mat_mul(rotation_z, p->vectors);
	free_matrix(rotation_z);
	free_matrix(p->projection);
	if (p->kind == ISOMETRIC)
		p->projection = get_isometric_projection(rotated_vectors);
	else if (p->kind == PARALLEL)
		p->projection = get_parallel_projection(rotated_vectors);
	free_matrix(rotated_vectors);
	scale_matrix(&p->projection, p->init_scale * pow(p->zoom_factor, p->zoom));
	translate_projection(&p->projection, p->translation_h, p->translation_v);
}
