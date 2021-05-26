/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   struct_modify.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mironbel <mironbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 16:52:51 by mironbel          #+#    #+#             */
/*   Updated: 2020/12/27 20:30:37 by mironbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_edge	*paste_edge(t_state *state, t_edge *tail, t_edge *edge)
{
	t_edge	*tmp;

	if (!edge)
		return (NULL);
	tmp = state->e;
	if (!tail)
		while (tmp->next)
			tmp = tmp->next;
	else
	{
		while (tmp != tail)
			tmp = tmp->next;
		edge->next = tmp->next->next;
	}
	tmp->next = edge;
	return (edge);
}

void	node_swap(void *x, void *y, size_t size)
{
	unsigned char	*p1;
	unsigned char	*p2;
	unsigned char	tmp;

	if (!x || !y)
		return ;
	p1 = (unsigned char *)x;
	p2 = (unsigned char *)y;
	while (size--)
	{
		tmp = *p1;
		*p1 = *p2;
		*p2 = tmp;
		p1++;
		p2++;
	}
}
