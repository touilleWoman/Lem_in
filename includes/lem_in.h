/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nabih <naali@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/26 17:03:23 by nabih             #+#    #+#             */
/*   Updated: 2019/11/20 06:17:02 by nabih            ###   ########.fr       */
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

#ifndef		LEM_IN_H
# define	LEM_IN_H

# include <includes.h>

# define LM_TRUE 1
# define LM_FALSE 0
# define LM_SUCCESS 1
# define LM_ERROR -1

typedef struct	s_path	t_path;
typedef struct	s_node	t_node;

struct					s_path//	Liste des chemins d'un seul noeud!!!
{
	uint32_t		id;//			static incrementer a la creation
	uint8_t			taken;//		Booleen Vrai ou Faux (Utiliser ou pas)
	int				weight;//		Poids == predecesseur + 1; =======> sera peut etre changer en unsigned
	t_path			*next;//		pointe sur le chemin suivant du meme noeud
};

struct					s_node//	Liste des noeuds a visiter ou deja visite
{
	uint32_t		id;//			static incrementer a la creation
	char			*name;//		Nom du noeud
	uint8_t			taken;//		Booleen Vrai ou Faux (Utiliser ou pas)
	t_path			*path_lst;//	Pointe sur 1er chemin de la liste des chemins connecter au noeud
	t_node			*next;//		Pointe sur le noeud suivant
};

/*
** Fonctions de Gestion
**      DES LISTES
*/

t_path					*new_path(/*voir info a transmettre*/);
void					del_path(t_path **start, uint32_t id);
void					clear_path(t_path **start);
void					swap_path(t_path *p1, t_path *p2);
t_path					get_last_path(t_path **start);

t_node					*new_node(/*voir info a transmettre*/);
void					del_node(t_node **start, uint32_t id);
void					clear_node(t_node **start);
void					swap_node(t_node *n1, t_node *n2);

#endif
