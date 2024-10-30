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

double	*parse_line(char *line)
{
	char	*wspace;
	double	*row;
	size_t	size;

	wspace = ft_strchr(line, ' ');
	row = (double *)malloc(sizeof(double));
	row[0] = ft_atoi(line);
	size = 1;
	while (wspace)
	{
		row = (double *)ft_realloc(row, sizeof(double) * (size + 1),
				sizeof(double) * size);
		row[size++] = ft_atoi(wspace);
		while (*wspace == ' ')
			wspace++;
		wspace = ft_strchr(wspace, ' ');
	}
	return (row);
}

double	**parse_map(const char *filename)
{
	double	**M;
	int		fd;
	char	*line;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	M = (double **)malloc(sizeof(double *));
	line = get_next_line(fd);
	M[0] = parse_line(line);
	free(line);
	return (M);
}
