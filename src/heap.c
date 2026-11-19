/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpanetta <rpanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 14:49:59 by rpanetta          #+#    #+#             */
/*   Updated: 2026/11/19 15:50:08 by rpanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

//allocates space for capacity nodes.
//If malloc fails, it returns 1.
//Otherwise the heap is left empty (size = 0).
int	heap_init(t_heap *heap, int capacity)
{
	heap->nodes = malloc(sizeof(t_heap_node) * capacity);
	if (heap->nodes == NULL)
		return (1);
	heap->size = 0;
	heap->capacity = capacity;
	return (0);
}

//free memory
void	heap_destroy(t_heap *heap)
{
	free(heap->nodes);
	heap->nodes = NULL;
	heap->size = 0;
}

//if the heap is full, it returns 1 (it cannot add an element).
//Otherwise it places the node at the end, increments the size,
//and moves it up to its proper position.
int	heap_push(t_heap *heap, t_heap_node node)
{
	if (heap->size >= heap->capacity)
		return (1);
	heap->nodes[heap->size] = node;
	heap->size++;
	heap_move_up(heap, heap->size - 1);
	return (0);
}

//to take out the smallest
t_heap_node	heap_pop(t_heap *heap)
{
	t_heap_node	smallest_node;

	smallest_node = heap->nodes[0];
	heap->size--;
	heap->nodes[0] = heap->nodes[heap->size];
	heap_move_down(heap, 0);
	return (smallest_node);
}
