/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isdigit.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/13 16:43:23 by hmorand           #+#    #+#             */
/*   Updated: 2024/08/13 16:43:23 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

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
/*
#include <stdio.h>

int	main(void)
{
	printf("Uppercase: %d\n", ft_isdigit('H));
	printf("Lowercase: %d\n", ft_isdigit('a));
	printf("Number: %d\n", ft_isdigit('5'));
}
 */
