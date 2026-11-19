/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rpanetta <rpanetta@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/11/10 18:12:36 by rpanetta          #+#    #+#             */
/*   Updated: 2026/11/19 15:57:51 by rpanetta         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "codexion.h"

int	main(int argc, char *argv[])
{
	t_config		config;
	t_simulation	simulation;

	if (argc != 9)
		return (print_error("Expected exactly 8 arguments"));
	if (parse_config(argv, &config))
		return (print_error("Invalid numeric argument"));
	if (config.number_of_coders == 0)
		return (print_error("The number of coders must be greater than 0"));
	if (validate_scheduler(config.scheduler))
		return (print_error("Scheduler must be fifo or edf"));
	simulation.config = config;
	if (init_simulation(&simulation) != 0)
		return (1);
	run_simulation(&simulation);
	destroy_simulation(&simulation);
	return (0);
}

//static void push_node(t_heap *heap, long long key, int coder_id)
//{
//    t_heap_node node;

//    node.key = key;
//    node.coder_id = coder_id;
//    if (heap_push(heap, node) != 0)
//        printf("push failed: heap is full\n");
//}

//int main(void)
//{
//    t_heap          heap;
//    t_heap_node     node;

//    if (heap_init(&heap, 5) != 0)
//        return (1);
//    push_node(&heap, 50, 2);
//    push_node(&heap, 20, 4);
//    push_node(&heap, 50, 0);
//    push_node(&heap, 10, 1);
//    push_node(&heap, 30, 3);
//    push_node(&heap, 99, 9);
//    while (heap.size > 0)
//    {
//        node = heap_pop(&heap);
//        printf("key = %lld, coder_id = %d\n", node.key, node.coder_id);
//    }
//    heap_destroy(&heap);
//    return (0);
//}