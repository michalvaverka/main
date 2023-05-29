/**
    @filename:  queue.h
    @author:    Michal Vaverka

    @description:
                Header file containing queue datatype and related functions.

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
                    2) The project bottowing this code IS NOT commercial, NOR accademical,
                    3) The creator of project borrowing this code will NOT present this project to a superior figure in his organization.

                Any usage in compliance with rules listed above is allowed.

                Michal Vaverka, 2023.
*/


#ifndef QUEUE_H
#define QUEUE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct
{
    int color_num;
    int neighbors_indexes[4];
    int index;
    bool *visited;
} node_t;

typedef struct 
{
    node_t *curr_node;
    int len;
    int color;
    void *next;
    void *prev;
} q_node_t;

typedef struct
{
    q_node_t *head;
    q_node_t *tail;
} queue_t;

q_node_t *create_node(node_t *node, int len, int color);

void push(queue_t *queue, q_node_t *to_push);

q_node_t *pop(queue_t *queue);

#endif