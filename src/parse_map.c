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

void parse_line(char *line, double** row1)
{
	double	*row;
	size_t	size;

	row = NULL;
	size = 0;
	while (line)
	{
		row = (double *)ft_realloc(row, sizeof(double) * (size + 1),
				sizeof(double) * size);
		row[size++] = ft_atoi(line);
		while (*line == ' ')
			line++;
		line = ft_strchr(line, ' ');
	}
	*row1 = row;
	return;
}

double	**parse_map(const char *filename)
{
	double	**M;
	int		fd;
	char	*line;
	size_t	size;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	line = get_next_line(fd);
	size = 0;
	M = NULL;
	while (line)
	{
		M = (double **)ft_realloc(M, sizeof(double *) * (size + 1),
				sizeof(double *) * size);
		parse_line(line, M+size);
		size++;
		free(line);
		line = get_next_line(fd);
	}
	return (M);
}
