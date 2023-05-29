/**
    @filename:  queue.c
    @author:    Michal Vaverka

    @description:
               Implementations of functions defined in queue.h

    @projectdescription: 
                The task was given as following: "We need to find an optimal way in the maze from point A to point B. 
                Maze contains walls, which are untraversable, unless we step on a button assigned to a specific wall. Only
                the last pressed button has an effect, i.e. the walls come back up after we press another button."

                I found out quickly, that the most efficient way to solve this problem was multilayer BFS.

                This task was given to me as a practical exam at subject ALG (algoritmization).
                
                I managed to get full points from this solution.

    @predisclaimer:
                Disclaimer and rules on usage are listed in order to avoid plagiarization in academic institutions.
    
    @disclaimer:
        !!! READ !!!
                Any part of this code can be used IF AND ONLY IF all of the following conditions hold:
                    1) The whole header of this file (from the @filename to the end of the @disclaimer section) must be pasted
                            directly above where the borrowed snippet/whole code is used,
                    2) The project borrowing this code IS NOT commercial, NOR accademical,
                    3) The creator of project borrowing this code will NOT present this project to a superior figure in his organization.

                Any usage in compliance with rules listed above is allowed.

                Michal Vaverka, 2023.
*/


#include <stdio.h>
#include <stdlib.h>

#include "queue.h"

q_node_t *create_node(node_t *node, int len, int color)
{
    q_node_t *ret = calloc(1, sizeof(q_node_t));

    ret->color = color;
    ret->len = len;
    ret->curr_node = node;

    return ret;
}

void push(queue_t *queue, q_node_t *to_push)
{
    if (queue->head == NULL)
    {
        queue->head = to_push;
        queue->tail = to_push;
    } else
    {
        queue->tail->next = to_push;
        to_push->prev = queue->tail;
        queue->tail = to_push;
    }

    //printf("pushed %d %d %d\n", to_push->curr_node->index, to_push->len, to_push->color);
}

q_node_t *pop(queue_t *queue)
{
    if (queue->head == NULL) return NULL;

    q_node_t *ret = queue->head;

    if (queue->head == queue->tail)
    {
        queue->head = NULL;
        queue->tail = NULL;
        return ret;
    }

    queue->head = queue->head->next;
    if (queue->head != NULL) queue->head->prev = NULL;

    return ret;
}
