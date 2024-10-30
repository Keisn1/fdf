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

void	*ft_realloc(void *ptr, size_t size, size_t cpy_size)
{
	void	*new;

	if (!ptr)
		return (malloc(size));
	;
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

unsigned int	parse_line(char *line, double **M_row, unsigned int **c_row)
{
	double			*row;
	unsigned int	*row_color;
	size_t			size;

	row = NULL;
	row_color = NULL;
	size = 0;
	while (line)
	{
		row = (double *)ft_realloc(row, sizeof(double) * (size + 1), sizeof(double) * size);
		row_color = (unsigned int *)ft_realloc(row_color, sizeof(unsigned int) * (size + 1), sizeof(unsigned int) * size);
		row_color[size] = 0x000000;
		row[size++] = ft_atoi(line);
		while (*line == ' ')
			line++;
		line = ft_strchr(line, ' ');
	}
	*M_row = row;
	*c_row = row_color;
	return (size);
}

t_map	new_map(void)
{
	return ((t_map){NULL, NULL, 0, 0});
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
		map.n = parse_line(line, map.map + map.m, map.color + map.m);
		map.m++;
		free(line);
		line = get_next_line(fd);
	}
	return (map);
}
