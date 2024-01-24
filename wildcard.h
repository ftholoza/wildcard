/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wildcard.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ftholoza <ftholoza@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/23 18:32:37 by ftholoza          #+#    #+#             */
/*   Updated: 2024/01/24 18:33:23 by ftholoza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef WILDCARD_H
# define WILDCARD_H

# include "dirent.h"
# include "stdlib.h"
# include "unistd.h"
# include "stdio.h"

typedef struct s_dlist
{
	void			*data;
	struct s_dlist	*prev;
	struct s_dlist	*next;
}	t_dlist;

typedef struct s_wildcard
{
	int		i;
	int		j;
	int		match;
	int		start_patern;
	char	*patern;
	char	*name;
}	t_wildcard;

char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*ft_strdup(const char *s);
int		ft_strlen(const char *str);
t_dlist	*add_element(char *str, t_dlist *env);
void	print_dlist(t_dlist *env);
void	ft_dl_clear(t_dlist **lst, void (*del)(void *));
void	*del(void *ptr);

#endif