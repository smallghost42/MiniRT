/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_atof.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferafano <ferafano@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 13:28:27 by ferafano          #+#    #+#             */
/*   Updated: 2024/12/07 14:23:54 by ferafano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

int ft_valid_int(const char *str)
{
	int i;
	int tmp;

	i = 0;
	if (str[i] == '\0')
		return (1);
	while (str[i] != '\0')
	{
		if (i == 0 && str[1] != '\0' && (str[i] == '-' || str[i] == '+'))
			i++;
		else if ((str[i] >= 48 && str[i] <= 57) || str[i] == '\n')
			i++;
		else
			return (1);
	}
	tmp = ft_atoi(str);
	if (tmp >= -2147483648 && tmp <= 2147483647)
		return (0);
	else
		return (1);
}

long ft_atoi(const char *nptr)
{
	int paire;
	int nb;

	nb = 0;
	paire = nb;
	while ((*nptr >= 9 && *nptr <= 13) || *nptr == 32)
		nptr++;
	while (*nptr == '+' || *nptr == '-')
	{
		if (*nptr == '-')
			paire++;
		nptr++;
		if (*nptr == '+' || *nptr == '-')
			return (0);
	}
	while (*nptr >= 48 && *nptr <= 57)
	{
		nb *= 10;
		nb += *nptr - 48;
		nptr++;
	}
	if (!(paire % 2))
		return (nb);
	return (-nb);
}

int is_valid_float(char *str, int x)
{
	int dot;
	int after;
	int i;

	dot = 0;
	after = 0;
	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '.')
		{
			dot++;
			if (dot > 1)
				return (1);
		}
		else if (i == 0 && str[1] != '\0' && (str[i] == '-' || str[i] == '+'))
			;
		else if (!isdigit(str[i]))
			return (1);
		else if (dot == 1)
		{
			after++;
			if (after > x)
				return (1);
		}
		i++;
	}
	return (0);
}

double ft_atof(const char *str)
{
	double result;
	double decimal_place;
	int is_decimal;
	int i;

	i = 0;
	result = 0;
	decimal_place = 0.1;
	is_decimal = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '.')
			is_decimal = 1;
		else
		{
			if (!is_decimal)
				result = result * 10 + (str[i] - '0');
			else
			{
				result += (str[i] - '0') * decimal_place;
				decimal_place /= 10;
			}
		}
		i++;
	}
	return (result);
}
