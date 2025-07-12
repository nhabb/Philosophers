/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/30 09:58:29 by nhaber            #+#    #+#             */
/*   Updated: 2025/07/12 12:59:40 by nhaber           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

void    set_boolean(mtx *mutex,bool *dest,bool val)
{
    handle_mutex(mutex,LOCK);
    *dest = val;
    handle_mutex(mutex,UNLOCK);
}

bool get_boolean(mtx *mutex,bool *val)
{
    bool ret;

    handle_mutex(mutex,LOCK);
    ret = *val;
    handle_mutex(mutex,UNLOCK);
    return (ret);
}


void set_long(mtx *mutex,long *dest,long val)
{
    handle_mutex(mutex,LOCK);
    *dest = val;
    handle_mutex(mutex,UNLOCK);
}

long get_long(mtx *mutex,long *val)
{
    bool ret;

    handle_mutex(mutex,LOCK);
    ret = *val;
    handle_mutex(mutex,UNLOCK);
    return (ret);
}

bool    sim_finished(t_data *data)
{
    return(get_boolean(&data->data_mutex,&data->sim_end));
}