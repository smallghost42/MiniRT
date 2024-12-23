/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_back_sphere.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: trazanad <trazanad@student.42antananari    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:22:53 by ferafano          #+#    #+#             */
/*   Updated: 2024/12/23 11:21:24 by trazanad         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

t_sphere *lstlast_sphere(t_sphere *lst)
{
	if (lst)
	{
		if (lst->next)
			return (lstlast_sphere(lst->next));
		else
			return (lst);
	}
	return (0);
}

void add_back_sphere(t_sphere **lst, t_sphere *new)
{
	if (lst)
	{
		if (*lst)
		{
			lstlast_sphere(*lst)->next = new;
		}
		else
			*lst = new;
	}
}
