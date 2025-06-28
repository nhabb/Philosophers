/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 14:59:32 by nhaber            #+#    #+#             */
/*   Updated: 2025/06/28 22:04:42 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


bool	ft_isspace(char c)
{
	if (c == ' ' || c == '\n' || c == '\t'
		|| c == '\v' || c == '\f' || c == '\r')
		return (true);
	return (false);
}

bool	ft_isdigit(int c)
{
	if (c >= '0' && c <= '9')
		return (true);
	return (false);
}

static const char *is_valid(const char *str)
{
    int len;
    const char *res;
    len = 0;
    while (ft_isspace(*str))
        *str++;
    if (*str == '+')
        *str++;
    else if (*str == '-')
    {
        printf("program only takes positive numbers!!\n");
        return (NULL);
    }
    if (!ft_isdigit(*str))
    {
        printf("Input must only be digits!!\n");
        return (NULL);
    }
    res = str;
    while(ft_isdigit(*str++))
        len++;
    if (len > 10)
    {
        printf("Number greater than int max.\n");
        return NULL;
    }
    return (res);
}

long  ft_atol(const char *str)
{
    long    result;

    result = 0;
    if (is_valid(str) == NULL)
        return -1;
    str = is_valid(str);
    while (ft_isdigit(*str))
        result = (result*10) + (*str++ - '0');
    if (result > INT_MAX)
    {
        printf("%ld is greater than maximum integer value.\n",result);
        return (-1);
    }
    return (result);
}
