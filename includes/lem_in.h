/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 17:03:23 by nabih             #+#    #+#             */
/*   Updated: 2019/12/18 15:07:49 by naali            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** INFORMATION IMPORTANTE !!!
** pour les types de retour
**
** "uint8_t" dans le cas d'un retour TRUE-FALSE
**
** "int8_t" dans le cas d'un retour SUCCESS-ERROR
*/

#ifndef LEM_IN_H
# define LEM_IN_H

# include <includes.h>

# define LM_TRUE 1
# define LM_FALSE 0
# define LM_SUCCESS 1
# define LM_ERROR -1
# define LM_IGNORE 0
# define LM_STOP 2
# define HASHCODE 10000

typedef struct s_path	t_path;
typedef struct s_node	t_node;

/*
** Liste des chemins d'un seul noeud!!!
** Static incrementer a la creation - modif de creation...
** La capacité résiduelle de flot, valeur peut etre 0, 1, ou 2
** Stockage de nom de noeud relier
** address de node lié à node en question
** pointe sur le chemin suivant du meme noeud
*/
struct					s_path
{
	uint32_t		id;
	uint8_t			flow;
	char			*name;
	t_node			*addr;
	t_path			*next;
};

/*
** Liste des noeuds a visiter ou deja visite
** Indice dans le tableau de HASH
** Nom du noeud
** address du node parent
** Nombre de chemin (Entrant ou sortant peu importe)
** Pointe sur 1er chemin de la liste des chemins connecter au noeud
** Pointe sur le noeud suivant
*/
struct					s_node
{
	uint32_t		id;
	char			*name;
	t_node			*parent_addr;
	uint32_t		nb_paths;
	t_path			*path_lst;
	t_node			*next;
};

typedef struct			s_lemin
{
	t_node			*tab[HASHCODE];
	char			*line;
	t_node			*start;
	t_node			*end;
	int32_t			nb_ants;
	int32_t			nb_nodes;
	int32_t			nb_paths;
	int32_t			dash;
	uint8_t			isstart;
	uint8_t			isend;
}						t_lemin;

/*
** Fonctions de Gestion
**   DES LISTES PATH
*/
t_path					*new_path(char *name, t_node *node);
void					pushback_path(t_path **start, t_path *node);
void					pushfront_path(t_path **start, t_path *node);
void					pushafter_path(t_path **start, uint32_t id,\
										t_path *node);
uint32_t				count_path(const t_path *start);
void					del_path(t_path **start, uint32_t id);
void					clear_path(t_path **start);
void					swap_id_path(t_path *p1, t_path *p2);
t_path					*get_last_path(t_path **start);
t_path					*get_path_by_id(t_path **start, uint32_t id);
t_path					*remove_from_path(t_path **start, uint32_t id,
											uint8_t flag);
void					send_path_away(t_path **src, t_path **dst, uint32_t id);
void					update_id_path(t_path **start);
void					free_path(t_path **path);

/*
** Fonctions de Gestion
**   DES LISTES NODE
*/
t_node					*new_node(char *name);
void					pushback_node(t_node **start, t_node *node);
void					pushfront_node(t_node **start, t_node *node);
void					pushafter_node(t_node **start, char *name,\
										t_node *node);
uint32_t				count_node(const t_node *start);
t_node					*get_last_node(t_node **start);
t_node					*get_node_by_name(t_node **start, char *name);
void					del_node(t_node **start, char *name);
void					clear_node(t_node **start);
t_node					*remove_from_node(t_node **start, char *name);
void					send_node_away(t_node **src, t_node **dst, char *name);
void					free_node(t_node **node);

/*
** Fonctions de Gestion
**    DES LISTE ANTS
*/
t_list					*init_ant_lst(int32_t nb);

/*
** Fonstions de Gestion
**   DES  ENCRYPTIONS
** Stocker dans l'id des noeuds
*/
int32_t					hash_name(char *name);

/*
** Fonstions de Gestion
**  DU TABLEAU DE HASH
*/
void					add_node_in_tab(t_lemin *lem, t_node *node);
uint8_t					node_exist(t_lemin *lem, char *name);
t_node					*get_node_in_hash(t_lemin *lem, char *name);
void					clear_hashtab(t_lemin *lem);

void					add_path_at_id(t_lemin *lem, t_path *pth, uint32_t id);
void					clear_hashpth(t_lemin *lem);

/*
** Fonctions de Gestion
**      DES TESTS
*/
void					print_tab(t_node *(tab[HASHCODE]), uint32_t max);
void					print_pth(t_path **tab);
void					print_info_inout(t_lemin *lem);

void					solver(t_lemin *lem);

#endif
