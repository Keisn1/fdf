/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/16 20:27/56 by kfreyer           #+#    #+#             */
/*   Updated: 2024/12/16 20:27:56 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

unsigned int	ft_hex_to_unsigned(char *hex_str)
{
	int				size;
	unsigned int	res;
	char			c;
	unsigned int	base;

	hex_str = hex_str + 2;
	size = 0;
	res = 0;
	base = 1;
	while (ft_isalnum(hex_str[size]))
		size++;
	while (--size)
	{
		c = hex_str[size];
		if (ft_isdigit(c))
			res += (c - '0') * base;
		else
		{
			c = ft_tolower(c);
			res += ((c - 'a') + 10) * base;
		}
		base *= 16;
	}
	return (res);
}

void	free_colors(unsigned int **colors, unsigned int rows)
{
	unsigned int	c1;

	c1 = 0;
	while (c1 < rows)
		free(colors[c1++]);
	free(colors);
}

void	reserve_space_vectors(size_t size, t_matrix *vectors)
{
	vectors->mat = malloc(3 * sizeof(double *));
	vectors->mat[0] = (double *)malloc(sizeof(double) * size);
	vectors->mat[1] = (double *)malloc(sizeof(double) * size);
	vectors->mat[2] = (double *)malloc(sizeof(double) * size);
}

t_matrix	map_to_vectors(t_map map)
{
	t_matrix	vectors;
	size_t		count;
	double		offset_x;
	double		offset_y;

	if (map.map.m == 0)
		return ((t_matrix){NULL, 0, 0});
	reserve_space_vectors(map.map.m * map.map.n, &vectors);
	vectors.m = 3;
	vectors.n = map.map.m * map.map.n;
	offset_x = -((map.map.n - 1) / 2.);
	offset_y = -((map.map.m - 1) / 2.);
	count = 0;
	while (count < vectors.n)
	{
		vectors.mat[0][count] = (count % map.map.n) + offset_x;
		vectors.mat[1][count] = (int)(count / map.map.n) + offset_y;
		vectors.mat[2][count] = map.map.mat[(int)(count / map.map.n)][(count
				% map.map.n)];
		count++;
	}
	return (vectors);
}

char	*advance_to_comma_or_ws(char *str)
{
	while (*str)
	{
		if (*str == ',' || *str == ' ')
			return (str);
		str++;
	}
	return (str);
}
