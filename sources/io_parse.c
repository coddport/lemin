/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   io_parse.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mironbel <mironbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 16:53:07 by mironbel          #+#    #+#             */
/*   Updated: 2020/12/27 20:30:54 by mironbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_node	*fill_node(t_state *state, int pass, t_node *node, char *x)
{
	char	*y;

	if (state->ant_s == 1 && (pass = -1))
		state->ant_s--;
	else if (state->ant_t == 1 && (pass = 1))
		state->ant_t--;
	if ((x = ft_strchr(state->line, ' ')))
	{
		*x = '\0';
		if (!(++x && (y = ft_strchr(x, ' ')) && x[0] != ' '))
			error("no y coordinate", state);
		*y = '\0';
		state->tmp = ft_itoa(ft_atoi(x));
		ft_strcmp(state->tmp, x) ? error("bad x", state) : free(state->tmp);
		state->tmp = ft_itoa(ft_atoi(++y));
		ft_strcmp(state->tmp, y) ? error("bad y", state) : free(state->tmp);
		if (!(node = init_node(state->line, ft_atoi(x), ft_atoi(y), pass)))
			error("node init failure", state);
		(pass == -1) ? state->s = node : 0;
		(pass == 1) ? state->t = node : 0;
		state->v_size++;
	}
	else if (!ft_strchr(state->line, '-'))
		error("no node data provided", state);
	return (node);
}

void	fill_nodes(t_state *state, int res, int i, t_node *tmp)
{
	t_node	*node;

	while ((res = get_next_line(state->fd, &state->line)) == 1)
	{
		if (state->ant_s == 1 && state->ant_t == 1)
			error("entrance exit mismatch", state);
		else if (!ft_strcmp(state->line, "##start"))
			(!state->s) ? state->ant_s = 1 : error("second start", state);
		else if (!ft_strcmp(state->line, "##end"))
			(!state->t) ? state->ant_t = 1 : error("second end", state);
		else if (*state->line == 'L' || *state->line == ' ' || !(*state->line))
			error("bad room name", state);
		else if (*state->line != '#')
		{
			if (!(node = fill_node(state, 0, NULL, NULL)))
				break ;
			(!node->is_pass) ? node->id = ++i : 0;
			(state->v) ? (tmp->next = node) : 0;
			(!state->v) ? (state->v = node) : 0;
			tmp = node;
		}
		ft_strdel(&state->line);
	}
	(res == -1) ? error("nodes read error", state) : 0;
	(state->ant_s || state->ant_t) ? error("no entrance or exit", state) : 0;
}

void	fill_edges(t_state *state, int flag)
{
	int		res;
	t_edge	*edge;
	t_edge	*tmp;
	char	*name;

	while (flag || ((res = get_next_line(state->fd, &state->line)) == 1))
	{
		if (*state->line == 'L' || *state->line == ' ')
			error("bad edge room name", state);
		else if (*state->line != '#' && !(name = ft_strchr(state->line, '-')))
			error("no edge data provided", state);
		if (*state->line != '#' && name)
		{
			*name = '\0';
			if (!(edge = init_edge(state->line, ++name, state->v)))
				error("edge initiation failure", state);
			(state->e) ? (tmp->next = edge) : 0;
			(!state->e) ? (state->e = edge) : 0;
			tmp = edge;
		}
		(flag) ? flag = 0 : 0;
		ft_strdel(&state->line);
	}
	(res == -1) ? error("edges read error", state) : 0;
}

void	add_nexts(t_state *state, int i)
{
	t_edge	*edge;
	t_list	*tmp;

	edge = state->e;
	while (edge)
	{
		if (!(tmp = ft_lstnew(edge->from, sizeof(t_node))))
			error("add list error", state);
		tmp->next = edge->to->nexts;
		edge->to->nexts = tmp;
		if (!(tmp = ft_lstnew(edge->to, sizeof(t_node))))
			error("add list error", state);
		tmp->next = edge->from->nexts;
		edge->from->nexts = tmp;
		edge = edge->next;
	}
	if (!(state->map = (char **)ft_memalloc(sizeof(char *) * state->v_size)))
		error("map init failure", state);
	if (!(state->phase = (t_quipu **)malloc(sizeof(t_quipu *) * state->total)))
		error("phrase failure", state);
	while (--i)
		state->phase[i] = NULL;
}

void	parse_data(t_state *state)
{
	if (get_next_line(state->fd, &state->line) > 0)
	{
		if ((state->total = ft_atoi(state->line)) < 1)
			error("ants: not enough ants", state);
		state->tmp = ft_itoa(state->total++);
		if (ft_strcmp(state->tmp, state->line))
			error("ants: non compliant line", state);
		ft_strdel(&state->line);
		free(state->tmp);
	}
	else
		error("ants: gnl error", state);
	fill_nodes(state, 0, 0, NULL);
	if (state->v_size > 15000)
		error("too many nodes", state);
	fill_edges(state, 1);
	state->t->id = state->v_size;
	state->v_size++;
	add_nexts(state, state->total);
}
