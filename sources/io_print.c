/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_print.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mironbel <mironbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 16:53:05 by mironbel          #+#    #+#             */
/*   Updated: 2020/12/27 18:42:49 by mironbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	print_state(t_state *state, t_node *tmp, t_edge *tmp2)
{
	ft_putnbr(state->total - 1);
	ft_putchar('\n');
	tmp = state->v;
	while (tmp)
	{
		if (tmp->is_pass)
			(tmp->is_pass > 0) ? ft_putendl("##end") : ft_putendl("##start");
		ft_putstr(tmp->name);
		ft_putchar(' ');
		ft_putnbr(tmp->coord_x);
		ft_putchar(' ');
		ft_putnbr(tmp->coord_y);
		ft_putchar('\n');
		tmp = tmp->next;
	}
	tmp2 = state->e;
	while (tmp2)
	{
		ft_putstr(tmp2->from->name);
		ft_putchar('-');
		ft_putendl(tmp2->to->name);
		tmp2 = tmp2->next;
	}
}

void	print_step(t_state *state, int a)
{
	ft_putchar('L');
	ft_putnbr(a);
	ft_putchar('-');
	ft_putstr(state->map[state->phase[a]->id / 2 + 1]);
	ft_putchar(' ');
}
