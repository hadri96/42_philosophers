/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strcat.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hmorand <hmorand@student.42lausanne.ch>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/28 17:02:25 by hmorand           #+#    #+#             */
/*   Updated: 2024/07/28 17:02:25 by hmorand          ###   ########.ch       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static	size_t	ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strcat(char *dest, const char *src)
{
	size_t	i;
	size_t	j;

	i = ft_strlen(dest);
	j = 0;
	while (src[j])
		dest[i++] = src[j++];
	dest[i] = '\0';
	return (dest);
}
/*
#include <stdio.h>
#include <string.h>

int	main(void)
{
	char src1[] = "world";
	char dest1[25] = "Hello ";

	printf("Test n°1 with homemade function: \"%s\"\n", ft_strcat(dest1, src1));

	char src2[] = "world";
	char dest2[25] = "Hello ";
	printf("Test n°1 with standard function: \"%s\"\n", strcat(dest2, src2));

	printf("---------------------------------------------\n");
	char src3[] = "lujah";
	char dest3[25] = "Halle";

	printf("Test n°2 with homemade function: \"%s\"\n", ft_strcat(dest3, src3));

	char src4[] = "lujah";
	char dest4[25] = "Halle";
	printf("Test n°2 with standard function: \"%s\"\n", strcat(dest4, src4));
}
 */
