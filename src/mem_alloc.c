/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mem_alloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: muokcan <muokcan@student.42kocaeli.com.tr  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/01/12 20:44:29 by muokcan           #+#    #+#             */
/*   Updated: 2026/01/12 22:08:08 by muokcan          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cub3d.h"
#include <stdlib.h>
#include <stdio.h>

static t_mem_manager	*get_mem(void)
{
	static t_mem_manager	mem_manager = {NULL, NULL, 0};

	return (&mem_manager);
}

void	*reg_alloc(size_t size)
{
	t_mem_manager	*mem_manager;
	t_all_mem		*new_mem;

	mem_manager = get_mem();
	new_mem = (t_all_mem *)malloc(sizeof(t_all_mem));
	if (!new_mem)
		return (NULL);
	new_mem->mem = malloc(size);
	if (!new_mem->mem)
	{
		free(new_mem);
		return (NULL);
	}
	new_mem->next = NULL;
	if (!mem_manager->head)
	{
		mem_manager->head = new_mem;
		mem_manager->tail = new_mem;
	}
	else
	{
		mem_manager->tail->next = new_mem;
		mem_manager->tail = new_mem;
	}
	mem_manager->allocated_blocks++;
	return (new_mem->mem);
}

void	free_all_mem(void)
{
	t_mem_manager	*mem_manager;
	t_all_mem		*current;
	t_all_mem		*next;

	mem_manager = get_mem();
	current = mem_manager->head;
	while (current)
	{
		next = current->next;
		free(current->mem);
		free(current);
		current = next;
	}
	mem_manager->head = NULL;
	mem_manager->tail = NULL;
	mem_manager->allocated_blocks = 0;
}

// void	print_mem_status(void)
// {
// 	t_mem_manager	*mem_manager;
//
// 	mem_manager = get_mem();
// 	printf("Allocated memory blocks: %zu\n", mem_manager->allocated_blocks);
// }
