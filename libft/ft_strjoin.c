/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kfreyer <kfreyer@student.42wolfsburg.      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/16 20:22:11 by kfreyer           #+#    #+#             */
/*   Updated: 2024/07/31 18:52:32 by kfreyer          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*res;
	size_t	size;

	size = ft_strlen(s1) + ft_strlen(s2) + 1;
	res = (char *)malloc((size) * sizeof(char));
	if (!res)
		return (NULL);
	*res = '\0';
	ft_strlcat(res, s1, size);
	ft_strlcat(res, s2, size);
	return (res);
}
