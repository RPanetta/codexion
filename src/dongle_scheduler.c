/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dongle_scheduler.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpanetta <rpanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/22 15:41:54 by rpanetta          #+#    #+#             */
/*   Updated: 2026/11/22 15:41:54 by rpanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

//Put the skipped coders back into the heap with their original keys,
//as if they'd never been removed.
static void restore_skipped_nodes(t_simulation *simulation, int count)
{
    while (count > 0)
    {
        count--;
        heap_push(&simulation->waiting_queue, simulation->skipped_nodes[count]);
    }
}

// look for the best coder who can already compile
// It removes coders from the heap in priority order (the smallest one first).
// If their dongles are ready, it found the one it was looking for: it stores it in ready_node and stops.
// If not, it stores it in skipped_nodes (the auxiliary notebook) and continues with the next one.
// At the end, it puts the skipped ones back into the heap and reports whether it found someone (1) or not (0).
int pop_ready_coder(t_simulation *simulation, t_heap_node *ready_node)
{
	t_heap		*queue;
	t_heap_node	node;
	int			skipped_count;
	int			found;

	queue = &simulation->waiting_queue;
	skipped_count = 0;
	found = 0;
	while (found == 0 && queue->size > 0)
	{
		node = heap_pop(queue);
		found = are_dongles_ready(simulation, node.coder_id);
		if (found == 1)
			*ready_node = node;
		else
		{
			simulation->skipped_nodes[skipped_count] = node;
			skipped_count++;
		}
	}
	restore_skipped_nodes(simulation, skipped_count);
	return (found);
}

int	assign_ready_dongles(t_simulation *simulation)
{
	t_heap_node	node;
	int			assigned_count;
	int			right_index;

	assigned_count = 0;
	while (pop_ready_coder(simulation, &node) == 1)
	{
		right_index = get_right_dongle_index(simulation, node.coder_id);
		simulation->dongles[node.coder_id].is_taken = 1;
		simulation->dongles[right_index].is_taken = 1;
		simulation->coders[node.coder_id].has_dongles = 1;
		assigned_count++;
	}
	return (assigned_count);
}
