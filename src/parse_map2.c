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

void	*ft_realloc(void *ptr, size_t size, size_t cpy_size)
{
	void	*new;

	if (!ptr)
		return (malloc(size));
	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	new = malloc(size);
	if (!new)
		return (NULL);
	new = ft_memcpy(new, ptr, cpy_size);
	free(ptr);
	return (new);
}

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

void	free_map(t_map map)
{
	unsigned int	c1;

	c1 = 0;
	while (c1 < map.map.m)
	{
		free(map.map.mat[c1]);
		free(map.color[c1]);
		c1++;
	}
	free(map.map.mat);
	free(map.color);
}

void	reserve_space_points(size_t size, t_matrix *points)
{
	points->mat = malloc(3 * sizeof(double *));
	points->mat[0] = (double *)malloc(sizeof(double) * size);
	points->mat[1] = (double *)malloc(sizeof(double) * size);
	points->mat[2] = (double *)malloc(sizeof(double) * size);
	points->m = 3;
	points->n = size;
}

t_matrix	map_to_vectors(t_map map)
{
	t_matrix	vectors;
	size_t		i;
	size_t		j;
	size_t		count;

	if (map.map.m == 0)
		return ((t_matrix){NULL, 0, 0});
	reserve_space_points(map.map.m * map.map.n, &vectors);
	i = 0;
	count = 0;
	while (i < map.map.m)
	{
		j = 0;
		while (j < map.map.n)
		{
			vectors.mat[0][count] = j;
			vectors.mat[1][count] = i;
			vectors.mat[2][count++] = map.map.mat[i][j++];
		}
		i++;
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
