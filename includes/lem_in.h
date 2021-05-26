/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mironbel <mironbel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/26 16:49:50 by mironbel          #+#    #+#             */
/*   Updated: 2020/12/27 20:31:57 by mironbel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H

# include "libft.h"
# include <stdio.h>
# include <fcntl.h>
# include <errno.h>

typedef struct		s_node
{
	char			*name;
	int				id;
	int				is_pass;
	int				coord_x;
	int				coord_y;
	int				to;
	int				from;
	int				ant_id;
	t_list			*nexts;
	struct s_node	*next;
}					t_node;

typedef struct		s_edge
{
	t_node			*from;
	t_node			*to;
	struct s_edge	*next;
}					t_edge;

typedef struct		s_quipu
{
	int				id;
	struct s_quipu	*data;
	struct s_quipu	*next;
}					t_quipu;

typedef struct		s_state
{
	t_node			*v;
	t_edge			*e;
	t_node			*s;
	t_node			*t;
	int				ant_s;
	int				ant_t;
	int				total;
	int				fd;
	int				flag[32];
	int				v_size;
	char			*line;
	t_quipu			**graph;
	t_quipu			**phase;
	t_quipu			*routes;
	char			**map;
	void			*tmp;
}					t_state;

void				parse_data(t_state *state);
void				map_roads(t_state *state, int *flow,
								t_quipu **allroads, int i);
void				move_ants(t_state *state, int *flow,
								t_quipu **allroads, void *tmp);
int					*generate_routes(t_state *state, int g_size, int *flow);

void				init_state(t_state *state);
t_quipu				*init_route(int id, t_quipu *data);
t_node				*init_node(char *name, int x, int y, int is_pass);
t_edge				*init_edge(char *name1, char *name2, t_node *nodes);
void				free_data(t_state *state, void *tmp, int i);

void				print_state(t_state *state, t_node *tmp, t_edge *tmp2);
void				print_step(t_state *state, int ant);
void				ft_getopt(t_state *state, int *ac, char ***av);
void				node_swap(void *x, void *y, size_t size);
int					error(char *str, t_state *state);

#endif
