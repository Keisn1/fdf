#include "fdf.h"
#include "libft.h"
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>

void *ft_realloc(void *ptr,  size_t size, size_t cpy_size) {
	if (!ptr)
		return malloc(size);;
	if (size == 0) {
		free(ptr);
		return NULL;
	}

	void* new = malloc(size);
	if (!new)
		return NULL;

	new = ft_memcpy(new, ptr, cpy_size);
	free(ptr);
	return new;
};

double	**parse_map(const char *filename)
{
	double	**M;
	int		fd;
	char	*line;
	char	*wspace;


	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);

	M = (double **)malloc(sizeof(double *));
	line = get_next_line(fd);
	wspace = ft_strchr(line, ' ');

	*M = (double *)malloc(sizeof(double));
	M[0][0] = ft_atoi(line);


	if (wspace)
	{
		M[0] = (double*)ft_realloc(M[0], sizeof(double)*2, sizeof(double));
		M[0][1] = ft_atoi(wspace);
	}

	free(line);
	return (M);
}
