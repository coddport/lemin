/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mironbel <mironbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 16:53:02 by mironbel          #+#    #+#             */
/*   Updated: 2020/12/26 17:03:23 by mironbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	init_state(t_state *state)
{
	int	j;

	if (!state)
		return ;
	state->v = NULL;
	state->e = NULL;
	state->s = NULL;
	state->t = NULL;
	state->total = 0;
	state->ant_s = -1;
	state->ant_t = -1;
	state->routes = NULL;
	state->fd = 0;
	state->v_size = 0;
	state->graph = NULL;
	state->phase = NULL;
	state->map = NULL;
	ft_memset(state->flag, 0, sizeof(int) * 32);
}

void	fill_graph(t_state *state, t_list *nexts, int id)
{
	t_node	*node;
	t_quipu	*tmp;

	if (id)
	{
		if (!(tmp = (t_quipu *)malloc(sizeof(t_quipu))))
			error("graph fill error", state);
		tmp->id = id + 1;
		tmp->next = state->graph[id];
		state->graph[id] = tmp;
		id++;
	}
	while (nexts)
	{
		node = (t_node *)nexts->content;
		if (node->id)
		{
			if (!(tmp = (t_quipu *)malloc(sizeof(t_quipu))))
				error("graph fill error", state);
			tmp->id = 2 * node->id - 1;
			tmp->next = state->graph[id];
			state->graph[id] = tmp;
		}
		nexts = nexts->next;
	}
}

void	make_residual(t_state *state, int g_size, int i)
{
	t_node	*node;
	t_quipu	*tmp;

	if (!(state->graph = (t_quipu **)malloc(sizeof(t_quipu *) * g_size)))
		error("graph init failure", state);
	while (i < g_size)
		state->graph[i++] = NULL;
	node = state->v;
	while (node)
	{
		if (node->is_pass == 0)
			fill_graph(state, node->nexts, 2 * node->id - 1);
		else if (node->is_pass == -1)
			fill_graph(state, node->nexts, 0);
		state->map[node->id] = node->name;
		node = node->next;
	}
	if (!(tmp = (t_quipu *)malloc(sizeof(t_quipu))))
		error("graph fill error", state);
	tmp->id = 0;
	tmp->next = state->graph[0];
	state->graph[0] = tmp;
}

int		main(int ac, char **av)
{
	t_quipu	**allroads;
	t_state	state;
	int		flow;

	init_state(&state);
	while (ac > 1 && av[1][0] == '-')
		ft_getopt(&state, &ac, &av);
	parse_data(&state);
	print_state(&state, NULL, NULL);
	make_residual(&state, 2 * state.v_size - 2, 0);
	free(generate_routes(&state, 2 * state.v_size - 2, &flow));
	if (!state.routes)
		error("no route found", &state);
	if (!(allroads = (t_quipu **)malloc(sizeof(t_quipu *) * flow)))
		error("roads failure", &state);
	map_roads(&state, &flow, allroads, -1);
	move_ants(&state, &flow, allroads, NULL);
	free_data(&state, NULL, -1);
	return (0);
}
