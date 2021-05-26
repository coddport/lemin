/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bfs_dfs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mironbel <mironbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 16:53:11 by mironbel          #+#    #+#             */
/*   Updated: 2020/12/27 18:38:35 by mironbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

static int		bfs_markup(t_state *state, int *markup, int cursor1,
					int cursor2)
{
	int		*seq;
	t_quipu	*tmp;
	int		i;

	if (!(seq = malloc(sizeof(int) * 2 * state->v_size - 2)))
		error("queue error", state);
	seq[cursor1++] = 0;
	while (cursor2 < cursor1)
	{
		tmp = state->graph[seq[cursor2]];
		while (tmp)
		{
			if (markup[tmp->id] == -1)
			{
				seq[cursor1++] = tmp->id;
				markup[tmp->id] = seq[cursor2];
			}
			tmp = tmp->next;
		}
		cursor2++;
	}
	free(seq);
	return (markup[2 * state->v_size - 3] != -1);
}

static t_quipu	*save_route(t_state *state, t_quipu **r, int id)
{
	static t_quipu	**run;
	t_quipu			*tmp;
	static int		max;

	if (id == 0)
		return (*r);
	if (!run)
		if (!(run = (t_quipu **)ft_memalloc(sizeof(t_quipu *) * 40000)))
			error("run error", state);
	if (run[id])
	{
		if ((*r)->id == max)
			run[id]->next = *r;
		*r = run[id];
	}
	else
	{
		if (!(tmp = init_route(id, NULL)))
			return (NULL);
		tmp->next = *r;
		*r = tmp;
		run[id] = *r;
		max = id;
	}
	return (*r);
}

static t_quipu	*dfs_markup(t_state *state, t_quipu *frm, int s, int *mark)
{
	t_quipu	*top;
	t_quipu	*prev;
	t_quipu	*r;

	if (frm->id == s)
		return (init_route(s, NULL));
	top = state->graph[frm->id];
	prev = NULL;
	while (top)
	{
		if ((mark[top->id] == frm->id) && (r = dfs_markup(state, top, s, mark)))
		{
			if (prev)
				prev->next = top->next;
			else
				state->graph[frm->id] = top->next;
			top->next = state->graph[top->id];
			state->graph[top->id] = top;
			top->id = frm->id;
			return (save_route(state, &r, frm->id));
		}
		prev = top;
		top = top->next;
	}
	return (NULL);
}

int				*generate_routes(t_state *state, int g_size, int *flow)
{
	int		*mark;
	t_quipu	*r;

	if (!(mark = (int *)malloc(sizeof(int) * g_size)))
		error("markup init failure", state);
	mark[0] = 40000;
	*flow = 0;
	while (1)
	{
		ft_memset(mark + 1, -1, (g_size - 1) * sizeof(int));
		if (bfs_markup(state, mark, 0, 0))
			while ((r = dfs_markup(state, state->graph[0], g_size - 1, mark)))
			{
				if (!(r = init_route(0, r)))
					error("route failure", state);
				r->next = state->routes;
				state->routes = r;
				if (++(*flow) == state->total)
					return (mark);
			}
		else
			return (mark);
	}
}
