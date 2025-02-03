/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handling.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lloginov <lloginov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 14:21:58 by lloginov          #+#    #+#             */
/*   Updated: 2025/02/03 14:34:22 by lloginov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void    free_exit1(t_cmd *exec, char *pointer, char *msg)
{
    (void)exec;
    if(pointer)
        free(pointer);
    printf("%s", msg);
}