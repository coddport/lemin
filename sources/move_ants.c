/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   move_ants.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mironbel <mironbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 16:52:59 by mironbel          #+#    #+#             */
/*   Updated: 2020/12/27 20:29:53 by mironbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"
#include <stdio.h>

static void	sort_roads(t_quipu **all, int *steps, int source, int sink)
{
	int	i;
	int	j;
	int	x;

	i = source;
	j = sink;
	x = source;
	if (source >= sink)
		return ;
	while (i < j)
	{
		while (steps[i] <= steps[x] && i < sink)
			i++;
		while (steps[j] > steps[x])
			--j;
		if (i < j)
		{
			node_swap(steps + i, steps + j, sizeof(int));
			node_swap(&(all[i]->data), &(all[j]->data), sizeof(t_quipu));
		}
	}
	node_swap(steps + x, steps + j, sizeof(int));
	node_swap(&(all[x]->data), &(all[j]->data), sizeof(t_quipu *));
	sort_roads(all, steps, source, j - 1);
	sort_roads(all, steps, j + 1, sink);
}

void		map_roads(t_state *state, int *flow, t_quipu **allroads, int i)
{
	t_quipu	*route;
	t_quipu	*tmp;
	int		*steps;

	if (!(steps = (int *)ft_memalloc(sizeof(int) * *flow)))
		error("len failure", state);
	route = state->routes;
	while (++i < *flow)
	{
		if (!(allroads[i] = (t_quipu *)ft_memalloc(sizeof(t_quipu))))
			error("path write failure", state);
		allroads[i]->data = route->data;
		steps[i] = 0;
		tmp = allroads[i]->data;
		while (tmp && ++steps[i])
			tmp = tmp->next;
		steps[i] = steps[i] / 2 + 1;
		route = route->next;
	}
	sort_roads(allroads, steps, 0, *flow - 1);
	i = 0;
	while (++i < *flow)
		allroads[i]->id = allroads[i - 1]->id + (steps[i] - steps[i - 1]) * i;
	free(steps);
}

void		pick_ant(t_state *state, int lead, int *prev)
{
	int		tmp;

	tmp = *prev - 1;
	ft_putchar('\n');
	while (++tmp < lead && !state->phase[tmp]->next)
		++(*prev);
	while (tmp < lead)
	{
		if (state->phase[tmp]->next)
		{
			state->phase[tmp] = state->phase[tmp]->next->next;
			print_step(state, tmp);
		}
		++tmp;
	}
}

void		move_ants(t_state *state, int *flow, t_quipu **allroads, void *tmp)
{
	int		lead;
	int		prev;
	int		fl;

	lead = 1;
	prev = 1;
	while (prev < state->total)
	{
		fl = 0;
		pick_ant(state, lead, &prev);
		while (lead < state->total && fl < *flow)
		{
			if (state->total - lead >= allroads[fl]->id)
			{
				state->phase[lead] = allroads[fl++]->data;
				print_step(state, lead++);
			}
			else
				while (*flow > fl && (tmp = (void *)allroads[--(*flow)]))
					ft_memdel(&tmp);
		}
	}
	while (fl >= 0)
		free(allroads[fl--]);
	free(allroads);
}
