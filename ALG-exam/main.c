/**
    @filename:  main.c
    @author:    Michal Vaverka

    @description:
                Main file containing all functionalities, except for the queue implementation.

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
#include <stdbool.h>

#include "queue.h"

typedef struct 
{
    int height;
    int width;
    int max_color;
    node_t *nodes;
} data_t;

void get_input(data_t *input)
{
    scanf(" %d %d %d", &input->height, &input->width, &input->max_color);

    input->nodes = calloc(sizeof(node_t), input->height * input->width);

    int temp;

    for (int i = 0; i < input->height; i++)
    {
        for (int j = 0; j < input->width; j++)
        {
            scanf(" %d", &temp);
            input->nodes[i * input->width + j].color_num = temp;
            input->nodes[i * input->width + j].index = i * input->width + j;
            
            if (j != input->width - 1) input->nodes[i * input->width + j].neighbors_indexes[0] =  i * input->width + j + 1;
            else input->nodes[i * input->width + j].neighbors_indexes[0] = -1;

            if (i != 0) input->nodes[i * input->width + j].neighbors_indexes[1] = (i - 1) * input->width + j;
            else input->nodes[i * input->width + j].neighbors_indexes[1] = -1;

            if (j != 0) input->nodes[i * input->width + j].neighbors_indexes[2] = i * input->width + (j - 1);
            else input->nodes[i * input->width + j].neighbors_indexes[2] = -1;
            
            if (i != input->height - 1) input->nodes[i * input->width + j].neighbors_indexes[3] = (i + 1) * input->width + j;
            else input->nodes[i * input->width + j].neighbors_indexes[3] = -1;

            input->nodes[i * input->width + j].visited = calloc(input->max_color + 1, sizeof(bool));
        }
    } 
}

void print_input(data_t *input)
{
    printf("%d %d %d\n", input->height, input->width, input->max_color);

    for (int i = 0; i < input->height; i++)
    {
        for (int j = 0; j < input->width; j++)
        {
            printf("%d ", input->nodes[i * input->width + j].color_num);
        }

        printf("\n");
    }
}

int BFS(data_t *data, queue_t *queue, const int finish_line)
{
    q_node_t *curr_q_node = pop(queue);
    node_t *curr_node;
    int next_color;

    while (curr_q_node != NULL)
    {
        curr_node = curr_q_node->curr_node;

        for (int i = 0; i < 4; i++)
        {
            next_color = curr_q_node->color;

            if (curr_node->neighbors_indexes[i] != -1)
            {
                //pokud maji zatarasy
                if (data->nodes[curr_node->neighbors_indexes[i]].color_num > 0)
                {
                    //muzeme projit jen s "klicem"
                    if (curr_q_node->color != data->nodes[curr_node->neighbors_indexes[i]].color_num) 
                    {
                        continue;
                    }
                } else if (data->nodes[curr_node->neighbors_indexes[i]].color_num != 0) //nemaji
                {
                    //musime do budoucna zmenit barvu cele cesty
                    next_color = -1 * data->nodes[curr_node->neighbors_indexes[i]].color_num;
                }

                //byl jsem tu levneji
                if (data->nodes[curr_node->neighbors_indexes[i]].visited[curr_q_node->color] == true) 
                {
                    continue;
                }

                push(queue, create_node(&data->nodes[curr_node->neighbors_indexes[i]], curr_q_node->len + 1, next_color));
                data->nodes[curr_node->neighbors_indexes[i]].visited[curr_q_node->color] = true;
            }

            if (curr_node->neighbors_indexes[i] == finish_line)
            {
                int res = curr_q_node->len + 1;
                //printf("Found it! with %d\n", res);
                free(curr_q_node);
                return res;
            }
        }

        free(curr_q_node);
        curr_q_node = pop(queue);
    }

    return -1;
}

int solve(data_t *data)
{
    int ret = 0;
    
    queue_t queue;
    
    queue.head = NULL;
    queue.tail = NULL;

    int first_index = (data->height - 1) * data->width;

    int finish_line = data->width - 1;

    for (int i = 0; i < data->max_color + 1; i++)
    {
        data->nodes[first_index].visited[i] = true;
    }

    push(&queue, create_node(&data->nodes[first_index], 0, 0));

    ret = BFS(data, &queue, finish_line);

    return ret;
}

int main()
{
    data_t data;
    get_input(&data);

    int res = solve(&data);

    printf("%d\n", res);
    return 0;
}
