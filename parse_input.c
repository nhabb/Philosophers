/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/28 15:05:24 by nhaber            #+#    #+#             */
/*   Updated: 2025/06/28 22:03:02 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"


bool parse_input(t_data *data,char **argv)
{
    // while (*argv)
    // {
    //     if (ft_atol(*argv) == -1)
    //         return (false);
    //     *argv++;
    // }
    if (ft_atol(argv[1]) == -1 || ft_atol(argv[2]) == -1
        || ft_atol(argv[3]) == -1 || ft_atol(argv[4]) == -1
        || ft_atol(argv[5]) == -1)
        return false;
    data->num_philo = (ft_atol(argv[1]));
    data->ttd = (ft_atol(argv[2])*1000);
    data->tte = (ft_atol(argv[3])*1000);
    data->tts = (ft_atol(argv[4])*1000);
    if (data->ttd < 60*1000 || data->tte < 60*1000
        || data->tts < 60*1000)
    {
        printf("use time stamps > 60ms\n");
        return false;
    }
    if (argv[5])
        data->num_meals = (ft_atol(argv[5]));
    else
        data->num_meals = -1;
    return (true);
}
