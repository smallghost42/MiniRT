/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   valid_atof.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ferafano <ferafano@student.42antananarivo  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 13:28:27 by ferafano          #+#    #+#             */
/*   Updated: 2024/12/07 14:09:58 by ferafano         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../mini.h"

int is_valid_float(char *str)
{
	int dot_count = 0;
	int after = 0;

	dot_count = 0;
	after = 0;
	for (int i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == '.')
		{
			dot_count++;
			if (dot_count > 1)
				return (1);
		}
		else if (!isdigit(str[i]))
			return 1;
		else if (dot_count == 1)
		{
			after++;
			if (after > 1)
				return (1);
		}
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
