/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_back_plane.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:27:34 by ferafano          #+#    #+#             */
/*   Updated: 2024/12/23 11:21:24 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_plane *lstlast_plane(t_plane *lst)
{
	if (lst)
	{
		if (lst->next)
			return (lstlast_plane(lst->next));
		else
			return (lst);
	}
	return (0);
}

void add_back_plane(t_plane **lst, t_plane *new)
{
	if (lst)
	{
		if (*lst)
		{
			lstlast_plane(*lst)->next = new;
		}
		else
			*lst = new;
	}
}
