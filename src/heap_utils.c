/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heap_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpanetta <rpanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/19 14:50:32 by rpanetta          #+#    #+#             */
/*   Updated: 2026/11/19 15:51:57 by rpanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

//Returns 1 if the first one should come out earlier, 0 otherwise
int	is_smaller_at(t_heap *heap, int first_index, int second_index)
{
	t_heap_node	first;
	t_heap_node	second;

	first = heap->nodes[first_index];
	second = heap->nodes[second_index];
	if (first.key < second.key)
		return (1);
	if (first.key > second.key)
		return (0);
	if (first.coder_id < second.coder_id)
		return (1);
	return (0);
}

void	swap_at(t_heap *heap, int first_index, int second_index)
{
	t_heap_node	temporary;

	temporary = heap->nodes[first_index];
	heap->nodes[first_index] = heap->nodes[second_index];
	heap->nodes[second_index] = temporary;
}

//As long as the node is smaller than its parent, they are swapped
//and it moves up one level.
//If it is no smaller than its parent, it stops (return ;)
//it is already in its correct position.
void	heap_move_up(t_heap *heap, int index)
{
	int	parent_index;

	while (index > 0)
	{
		parent_index = (index - 1) / 2;
		if (is_smaller_at(heap, index, parent_index) == 0)
			return ;
		swap_at(heap, index, parent_index);
		index = parent_index;
	}
}

void	heap_move_down(t_heap *heap, int index)
{
	int	smallest_index;
	int	left_index;
	int	right_index;

	while (index * 2 + 1 < heap->size)
	{
		left_index = index * 2 + 1;
		right_index = index * 2 + 2;
		smallest_index = left_index;
		if (right_index < heap->size
			&& is_smaller_at(heap, right_index, left_index) == 1)
			smallest_index = right_index;
		if (is_smaller_at(heap, smallest_index, index) == 0)
			return ;
		swap_at(heap, index, smallest_index);
		index = smallest_index;
	}
}
