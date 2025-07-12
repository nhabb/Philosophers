// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   handle_mutex.c                                     :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/06/29 09:35:07 by nhaber            #+#    #+#             */
// /*   Updated: 2025/07/02 22:43:35 by nhaber           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "philo.h"

// void *handle_malloc(size_t size)
// {
//     void *res;

//     res = malloc(size);
//     if (res == NULL)
//     {
//         printf ("Malloc failed");
//         return NULL;
//     }
//     return (res);
// }

// void handle_mutex(mtx *mutex, t_opcode opcode)
// {
//     if (opcode == LOCK)
//         handle_error(pthread_mutex_lock(mutex),opcode);
//     else if (opcode == UNLOCK)
//         handle_error(pthread_mutex_unlock(mutex),opcode);
//     else if (opcode == INIT)
//         handle_error(pthread_mutex_init(mutex,NULL),opcode);
//     else if (opcode == DESTROY)
//         handle_error(pthread_mutex_destroy(mutex),opcode);
//     else
//     {
//         printf("Opcode not available.\n");
//         return ;
//     }
// }

// static void handle_error(int status, t_opcode opcode)
// {
//     if (status == 0)
//       return ;
//     if (EINVAL == status && (opcode == LOCK || opcode == UNLOCK))
//     {
//         printf("The value specified by mutex is invalid.\n");
//         return ;
//     }
//     else if (EINVAL == status && opcode == INIT)
//     {
//         printf("The value specified by attr is invalid.\n");
//         return ;
//     }
//     else if (EDEADLK == status)
//     {
//         printf("A deadlock would occur if the thread blocked waiting for mutex\n");
//         return;
//     }
//     else if (EPERM == status)
//     {
//         printf("The current thread does not hold a lock on mutex.\n");
//         return ;
//     }
//     if (handle_error_helper(status,opcode))
//         return ;
// }

// static bool handle_error_helper(int status,t_opcode opcode)
// {
//     if (ENOMEM == status)
//     {
//         printf("Not enough memory.\n");
//         return true;
//     }
//     else if (EBUSY == status)
//     {
//         printf("mutex id locked.\n");
//         return true;
//     }
//     return (false);
// }