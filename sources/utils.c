/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mironbel <mironbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 16:52:47 by mironbel          #+#    #+#             */
/*   Updated: 2020/12/26 17:06:36 by mironbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		error(char *str, t_state *state)
{
	errno = 1;
	if (state->flag['v' - 'a'])
		perror(str);
	else
		write(2, "ERROR\n", 6);
	exit(1);
}

void	ft_getopt(t_state *state, int *ac, char ***av)
{
	int	j;
	int flag;

	flag = 0;
	(*ac)--;
	(*av)++;
	j = 0;
	while ((**av)[++j] && (**av)[j] >= 'a' && (**av)[j] <= 'z')
	{
		if ((**av)[j] == 'h')
			error("available options:\n-f (file input) \n-v (debug)", state);
		if ((**av)[j] == 'f' && state->flag['f' - 'a'] == 0)
			flag = 1;
		state->flag[(**av)[j] - 'a'] = 1;
	}
	if ((**av)[j])
		error("invalid option", state);
	if (flag)
	{
		(*av)++;
		(*ac)--;
		if ((state->fd = open((**av), O_RDONLY)) < 1)
			error("file input format:\n-f filename", state);
	}
}
