/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afantini <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/21 10:27:43 by afantini          #+#    #+#             */
/*   Updated: 2022/05/21 11:31:18 by afantini         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const*s1, char const*s2)
{
	char	*str;
	int		i;
	int		j;

	str = malloc(ft_strlen(s1) + ft_strlen(s2) + 1);
	if (str == NULL)
		return (0);
	i = 0;
	j = 0;
	while (i < (int)ft_strlen(s1) + (int)ft_strlen(s2))
	{
		while (s1[i] != '\0')
		{
			str[i] = (char)s1[i];
			i++;
		}
		while (s2[j] != '\0')
		{
			str[i] = (char)s2[j];
			i++;
			j++;
		}
	}
	str[i] = '\0';
	return (str);
}

/*int    main()
{
	char    strs[] = "du888";
	char    separator[] = "dweio89";
	
	printf("%s", ft_strjoin(strs, separator));
}*/
