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
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

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

t_map	new_map(void)
{
	return ((t_map){NULL, NULL, 0, 0});
}

unsigned int	parse_line(char *line, double **M_row, unsigned int **c_row)
{
	size_t	size;

	*M_row = NULL;
	*c_row = NULL;
	size = 0;
	while (line)
	{
		while (*line == ' ')
			line++;
		*M_row = (double *)ft_realloc(*M_row, sizeof(double) * (size + 1),
				sizeof(double) * size);
		*c_row = (unsigned int *)ft_realloc(*c_row, sizeof(unsigned int) * (size
					+ 1), sizeof(unsigned int) * size);
		(*c_row)[size] = 0x000000;
		(*M_row)[size] = ft_atoi(line);
		line = advance_to_comma_or_ws(line);
		if (*line == ',')
			(*c_row)[size] = ft_hex_to_unsigned(line);
		size++;
		line = ft_strchr(line, ' ');
		/* if (size == 10) { */
		/* 	ft_putnbr_fd((int)size, STDOUT_FILENO); */
		/* 	ft_putendl_fd("", STDOUT_FILENO); */
		/* 	ft_putnbr_fd(ft_strlen(line), STDOUT_FILENO); */
		/* 	ft_putendl_fd("", STDOUT_FILENO); */
		/* 	ft_putendl_fd("", STDOUT_FILENO); */
		/* } */
	}
	return (size);
}

t_map	parse_map(const char *filename)
{
	t_map	map;
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return ((t_map){NULL, NULL, 0, 0});
	line = get_next_line(fd);
	map = new_map();
	while (line)
	{
		map.map = (double **)ft_realloc(map.map, sizeof(double *) * (map.m + 1),
				sizeof(double *) * map.m);
		map.color = (unsigned int **)ft_realloc(map.color,
				sizeof(unsigned int *) * (map.m + 1), sizeof(unsigned int *)
				* map.m);
		if (!map.map || !map.color)
			return ((t_map){NULL, NULL, 0, 0});
		map.n = parse_line(line, map.map + map.m, map.color + map.m);
		map.m++;
		free(line);
		line = get_next_line(fd);
	}
	close(fd);
	return (map);
}

t_mat	extract_points(t_map map)
{
	unsigned int	size;
	t_mat			points;
	size_t			i;
	size_t			j;
	size_t			count;

	if (map.m == 0)
		return ((t_mat){NULL, 0, 0});
	size = map.m * map.n;
	points.mat = (double **)malloc(sizeof(double *) * 3);
	points.mat[0] = (double *)malloc(sizeof(double) * size);
	points.mat[1] = (double *)malloc(sizeof(double) * size);
	points.mat[2] = (double *)malloc(sizeof(double) * size);

	i = 0;
	count = 0;
	while (i < map.m)
	{
		j = 0;
		while (j < map.n)
		{
			points.mat[0][count] = j;
			points.mat[1][count] = i;
			points.mat[2][count] = map.map[i][j];
			count++;
			j++;
		}
		i++;
	}
	points.m = 3;
	points.n = size;
	return (points);
}
