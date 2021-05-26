/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isint.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mironbel <mironbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 19:31:21 by cport             #+#    #+#             */
/*   Updated: 2020/12/26 16:48:22 by mironbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/libft.h"

int		is_int(char *str, int sign, int i)
{
	char	*minmax;
	int		len;

	minmax = "2147483647";
	if (*str == '+' || *str == '-')
	{
		sign = (str[0] == '-') ? 1 : 0;
		str++;
	}
	if ((len = ft_strlen(str)) > 10)
		return (0);
	else if (len == 10)
		while (++i < len)
		{
			if ((i == 9) && (str[i] - '0') > (minmax[i] - '0' + sign))
				return (0);
			else if ((i < 9) && (str[i] - '0') > (minmax[i] - '0'))
				return (0);
		}
	return (1);
}
