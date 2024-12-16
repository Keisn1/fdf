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

bool	is_end_of_line(char *line)
{
	if (!line)
		return (true);
	while (*line == ' ')
		line++;
	if (*line == '\n' || *line == 0)
		return (true);
	return (false);
}

unsigned int	parse_line(char *line, double **M_row, unsigned int **c_row,
		unsigned int size)
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
		if (is_end_of_line(line))
			break ;
	}
	return (size);
}

unsigned int	get_length_line(char *line)
{
	unsigned int	size;

	size = 0;
	if (is_end_of_line(line))
		return (size);
	while (true)
	{
		while (*line == ' ')
			line++;
		line = ft_strchr(line, ' ');
		size++;
		if (is_end_of_line(line))
			break ;
	}
	return (size);
}

t_map	resize_map(t_map map)
{
	t_map			new_map;
	unsigned int	count;

	new_map.map.m = map.map.m + 1;
	new_map.map.n = map.map.n;
	new_map.map.mat = (double **)malloc(sizeof(double *) * (new_map.map.m));
	new_map.color = (unsigned int **)malloc(sizeof(unsigned int *)
			* (new_map.map.m));
	if (!new_map.map.mat || !new_map.color)
		return ((t_map){(t_matrix){NULL, 0, 0}, NULL});
	count = 0;
	while (count < map.map.m)
	{
		new_map.map.mat[count] = map.map.mat[count];
		new_map.color[count] = map.color[count];
		count++;
	}
	free(map.map.mat);
	free(map.color);
	return (new_map);
}

t_map	parse_map(const char *filename)
{
	t_map	map;
	int		fd;
	char	*line;
	int		count;

	map = ((t_map){(t_matrix){NULL, 0, 0}, NULL});
	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (map);
	line = get_next_line(fd, false);
	map.map.n = get_length_line(line);
	map.map.m = 0;
	count = 0;
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
