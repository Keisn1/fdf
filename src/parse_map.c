/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 13:55/17 by kfreyer           #+#    #+#             */
/*   Updated: 2024/10/30 13:55:17 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "libft.h"

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


bool end_of_line(char *line) {
	if (!line)
		return true;
	while (*line == ' ')
		line++;
	if (*line == '\n' || *line == 0)
		return true;
	return false;
}

unsigned int	parse_line(char *line, double **M_row, unsigned int **c_row, unsigned int size)
{
	size_t	count;

	*M_row = NULL;
	*c_row = NULL;
	count = 0;

	*M_row = (double *)malloc(size * sizeof(double));
	*c_row = (unsigned int *)malloc(size * sizeof(unsigned int));
	while (true)
	{
		while (*line == ' ')
			line++;
		(*c_row)[count] = 0xFF00FF;
		(*M_row)[count] = ft_atoi(line);
		line = advance_to_comma_or_ws(line);
		if (*line == ',')
			(*c_row)[count] = ft_hex_to_unsigned(line);
		count++;
		line = ft_strchr(line, ' ');
		if (end_of_line(line))
			break;
	}
	return (size);
}

unsigned int get_length_line(char *line) {
	unsigned int size = 0;

	if (end_of_line(line))
		return size;
	while (true) {
		while (*line == ' ')
			line++;
		line = ft_strchr(line, ' ');
		size++;
		if (end_of_line(line))
			break;
	}
	return size;
}

t_map resize_map(t_map map) {
	t_map new_map;

	new_map.map.m = map.map.m + 1;
	new_map.map.n = map.map.n;
	new_map.map.mat = (double **)malloc(sizeof(double *) * (new_map.map.m));
	new_map.color = (unsigned int **)malloc( sizeof(unsigned int *) * (new_map.map.m));

	if (!new_map.map.mat || !new_map.color)
		return ((t_map){(t_matrix){NULL, 0, 0}, NULL});

	unsigned int count = 0;
	while (count < map.map.m) {
		new_map.map.mat[count] = map.map.mat[count];
		new_map.color[count] = map.color[count];
		count++;
	}
	free(map.map.mat);
	free(map.color);
	return new_map;
}

t_map	parse_map(const char *filename)
{
	t_map	map;
	int		fd;
	char	*line;

	map = ((t_map){(t_matrix){NULL, 0, 0}, NULL});
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return map;
	line = get_next_line(fd, false);
	map.map.n = get_length_line(line);
	map.map.m = 0;
	int count = 0;
	while (line)
	{
		map = resize_map(map);
		parse_line(line, map.map.mat + count, map.color + count, map.map.n);
		count++;
		free(line);
		line = get_next_line(fd, false);
	}
	close(fd);
	return (map);
}

void reserve_space_points(size_t size, t_matrix *points) {
	points->mat = malloc(3 * sizeof(double*));
	points->mat[0] = (double *)malloc(sizeof(double) * size);
	points->mat[1] = (double *)malloc(sizeof(double) * size);
	points->mat[2] = (double *)malloc(sizeof(double) * size);
	points->m = 3;
	points->n = size;
}

t_matrix	map_to_vectors(t_map map)
{
	t_matrix			points;
	size_t			i;
	size_t			j;
	size_t			count;

	if (map.map.m == 0)
		return ((t_matrix){NULL, 0, 0});
	reserve_space_points(map.map.m * map.map.n, &points);

	i = 0;
	count = 0;
	while (i < map.map.m)
	{
		j = 0;
		while (j < map.map.n)
		{
			points.mat[0][count] = j;
			points.mat[1][count] = i;
			points.mat[2][count++] = map.map.mat[i][j++];
		}
		i++;
	}
	return (points);
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
