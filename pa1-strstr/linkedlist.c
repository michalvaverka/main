/**
    @filename:  linkedlist.c
    @author:    Michal Vaverka

    @description:
                Implementations of functions defined in linkedlist.h

    @projectdescription: 
                This project is one of the PA1 exams at FIT-CTU, I solved it in my spare time because my two friends
                were getting ready for that exam and I wanted to provide them with a few working solutions.

                The task was to implement searching for needles in a haystack (same as strstr), except that here
                it is required to return all found needles sorted ascending by the iteration of occurence.

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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "linkedlist.h"

page_t *createPage(int number) 
{
    page_t *ret = (page_t *) malloc(sizeof(page_t));

    ret->number = number;
    ret->next = NULL;

    return ret;
}

linkedList_t *createListFromString(const char *string) 
{
    linkedList_t *ret = (linkedList_t *) malloc(sizeof(linkedList_t));

    ret->head = NULL;

    int i = strlen(string) - 1;

    for (; i >= 0; i--) push(ret, createPage(string[i] - '0'));

    return ret;
}

void push(linkedList_t *list, page_t *toPush) 
{
    if (list->head == NULL) 
    {
        list->head = toPush;
    } else 
    {
        toPush->next = list->head;
        list->head = toPush;
    }
}

void add(linkedList_t *list, page_t *toAdd) 
{
    if (list->head == NULL) 
    {
        list->head = toAdd; 
        return;
    }

    page_t *currPage = list->head;

    while (currPage->next != NULL) currPage = currPage->next;

    currPage->next = toAdd;
}

void clearList(linkedList_t *list) 
{
    page_t *currPage = list->head;
    page_t *temp = NULL;

    while (currPage != NULL) 
    {
        temp = currPage->next;
        free(currPage);
        currPage = temp;
    }

    free(list);
}

void printList(linkedList_t *list) 
{
    char *string = toString(list);

    printf("%s\n", string);

    free(string);
}

char *toString(linkedList_t *list) 
{
    int capacity = 1;
    int size = 0;

    char *ret = malloc(sizeof(capacity));

    page_t *currPage = list->head;

    while (currPage != NULL) 
    {
        if (size == capacity) 
        {
            capacity++;
            ret = realloc(ret, capacity);
        }

        ret[size] = currPage->number + '0';
        size++;

        currPage = currPage->next;
    }

    if (size == capacity) ret = realloc(ret, capacity + 1);

    ret[size] = '\0';

    return ret;
}
