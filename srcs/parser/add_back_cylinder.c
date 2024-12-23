/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_back_cylinder.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:29:06 by ferafano          #+#    #+#             */
/*   Updated: 2024/12/23 11:21:24 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_cylinder *lstlast_cylinder(t_cylinder *lst)
{
	if (lst)
	{
		if (lst->next)
			return (lstlast_cylinder(lst->next));
		else
			return (lst);
	}
	return (0);
}

void add_back_cylinder(t_cylinder **lst, t_cylinder *new)
{
	if (lst)
	{
		if (*lst)
		{
			lstlast_cylinder(*lst)->next = new;
		}
		else
			*lst = new;
	}
}
