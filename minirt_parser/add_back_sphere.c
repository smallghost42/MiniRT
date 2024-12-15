/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   add_back_shape.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferafano <ferafano@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/15 11:22:53 by ferafano          #+#    #+#             */
/*   Updated: 2024/12/15 11:26:34 by ferafano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

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
