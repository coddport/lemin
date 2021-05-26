/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_del.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mironbel <mironbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/28 18:09:41 by mironbel          #+#    #+#             */
/*   Updated: 2020/12/28 18:12:51 by mironbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	free_structs(t_state *state, void *tmp, int i)
{
	while (state->v && (tmp = (void *)state->v))
	{
		while (state->v->nexts)
		{
			tmp = state->v->nexts->content;
			ft_memdel(&tmp);
			tmp = state->v->nexts;
			state->v->nexts = state->v->nexts->next;
			ft_memdel(&tmp);
		}
		tmp = state->v;
		state->v = state->v->next;
		ft_memdel(&tmp);
	}
	while (i--)
		while (state->graph[i])
		{
			tmp = state->graph[i];
			state->graph[i] = state->graph[i]->next;
			ft_memdel(&tmp);
		}
	free(state->graph);
}

void	free_data(t_state *state, void *tmp, int i)
{
	while (++i < state->v_size)
		free(state->map[i]);
	while (state->e && (tmp = (void *)state->e))
	{
		state->e = state->e->next;
		ft_memdel(&tmp);
	}
	free(state->map);
	free(state->phase);
	ft_memdel(&tmp);
	while (state->routes && (tmp = (void *)state->routes))
	{
		state->routes = state->routes->next;
		ft_memdel(&tmp);
	}
	free_structs(state, NULL, 2 * state->v_size - 2);
}
