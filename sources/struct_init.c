/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_init.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mironbel <mironbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 16:52:32 by mironbel          #+#    #+#             */
/*   Updated: 2020/12/27 20:31:06 by mironbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_node	*init_node(char *name, int x, int y, int is_pass)
{
	t_node	*node;

	if (!(node = (t_node *)malloc(sizeof(t_node))))
		return (NULL);
	node->name = ft_strdup(name);
	node->coord_x = x;
	node->coord_y = y;
	node->nexts = NULL;
	node->next = NULL;
	node->is_pass = is_pass;
	node->from = 0;
	node->to = 0;
	node->id = 0;
	return (node);
}

t_edge	*init_edge(char *name1, char *name2, t_node *nodes)
{
	t_edge	*edge;
	t_node	*tmp;

	if (!(edge = (t_edge *)malloc(sizeof(t_edge))))
		return (NULL);
	edge->from = NULL;
	edge->to = NULL;
	edge->next = NULL;
	tmp = nodes;
	while (tmp)
	{
		if (name1 && !ft_strcmp(tmp->name, name1))
			edge->from = tmp;
		if (name2 && !ft_strcmp(tmp->name, name2))
			edge->to = tmp;
		tmp = tmp->next;
	}
	if (!edge->from || !edge->to)
		return (NULL);
	return (edge);
}

t_quipu	*init_route(int id, t_quipu *data)
{
	t_quipu	*route;

	if (!(route = (t_quipu *)malloc(sizeof(t_quipu))))
		return (NULL);
	route->id = id;
	route->data = data;
	route->next = NULL;
	return (route);
}
