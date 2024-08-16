/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_str_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/16 17:41:26 by hmorand           #+#    #+#             */
/*   Updated: 2024/08/16 17:41:26 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	ft_isdigit(int c)
{
	if (c < '0' || c > '9')
		return (0);
	return (1);
}

bool	ft_strisdigit(char *str)
{
	while (*str)
	{
		if (!ft_isdigit(*str) && *str != '-')
			return (false);
		str++;
	}
	return (true);
}

size_t	ft_strlen(const char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*result;
	size_t	size;
	size_t	i;

	size = ft_strlen(s);
	if (size < start + len && size > start)
		len = size - start;
	else if (size <= start)
	{
		len = 0;
		start = 0;
	}
	result = malloc(sizeof(char) * len + 1);
	if (!result)
		return (NULL);
	i = 0;
	while (s[start] && len)
	{
		len--;
		result[i++] = s[start++];
	}
	result[i] = '\0';
	return (result);
}
