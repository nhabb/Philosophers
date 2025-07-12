// /* ************************************************************************** */
// /*                                                                            */
// /*                                                        :::      ::::::::   */
// /*   handle_thread.c                                    :+:      :+:    :+:   */
// /*                                                    +:+ +:+         +:+     */
// /*   By: nhaber <nhaber@student.42.fr>              +#+  +:+       +#+        */
// /*                                                +#+#+#+#+#+   +#+           */
// /*   Created: 2025/06/29 10:02:51 by nhaber            #+#    #+#             */
// /*   Updated: 2025/07/02 15:25:29 by nhaber           ###   ########.fr       */
// /*                                                                            */
// /* ************************************************************************** */

// #include "philo.h"

// static void thread_error(int status, t_opcode opcode)
// {
//     if (status == 0)
//         return ;
//     if (EAGAIN == status)
//     {
//         printf("Error: No resources to create another thread\n");
//         return ;
//     }
//     else if (EPERM == status)
//     {
//         printf("Error: The caller does not have appropriate permission\n");
//         return ;
//     }
//     else if (EINVAL == status && opcode == CREATE)
//     {
//         printf("Error: The value specified by attr is invalid\n");
//         return ;
//     }else if (EINVAL == status && (opcode == JOIN || opcode == DETACH))
//     {
//         printf("Error: The value specified by thread is not joinable\n");
//         return ;
//     }
//     if (thread_error_helper(status,opcode))
//         return ;
// }


// static bool thread_error_helper(int status, t_opcode opcode)
// {
//     if (ESRCH == status)
//     {
//         printf("Error: No thread could be found corresponding to the given thread ID\n");
//         return (true);
//     }
//     else if (EDEADLK == status)
//     {
//         printf("Error: No thread could be found corresponding to the given thread ID\n");
//         return (true);
//     }
//     return (false);
// }

// void handle_thread(pthread_t *thread,void *(*foo)(void *)
//                 ,void *data, t_opcode opcode)
// {
//     if (opcode == CREATE)
//         thread_error(pthread_create(thread,NULL,foo,data),opcode);
//     else if (opcode == JOIN)
//         thread_error(pthread_join(*thread,NULL),opcode);
//     else if (opcode == DETACH)
//         thread_error(pthread_detach(*thread),opcode);
//     else
//     {
//         printf("Opcode not available");
//         return ;
//     }
// }