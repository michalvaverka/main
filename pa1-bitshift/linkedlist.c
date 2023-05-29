/**
    @filename:  linkedlist.c
    @author:    Michal Vaverka

    @description:
                Implementations of functions defined in linkedlist.h

    @projectdescription: 
                This project is one of the PA1 exams at FIT-CTU, I solved it in my spare time because my two friends
                were getting ready for that exam and I wanted to provide them with a few working solutions.

                The task was to implement a representation of a Linked list in hexadecimal number and perform a left-shift
                on it. I expanded this solution by a right-shift.

                Head of list is the least-signifficant digit.

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


page_t *createPage(char number) 
{
    page_t *ret = (page_t *) malloc(sizeof(page_t));

    ret->number = number;
    ret->next = NULL;

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
    if (list == NULL) return;

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
    if (list->head == NULL) return;

    char *listString = linkedListToString(list);
    printf("%s\n", listString);

    free(listString);
}

linkedList_t *createLinkedListString(const char *string) 
{
    linkedList_t *ret = (linkedList_t *) malloc(sizeof(linkedList_t));
    ret->head = NULL;

    int index = 0;

    while (string[index] != '\0') 
    {
        push(ret, createPage(string[index]));
        index++;
    }

    return ret;
}

char *linkedListToString(linkedList_t *toString) 
{
    int size = 0;
    int capacity = 1;
    char *reversedString = malloc(capacity);

    page_t *currPage = toString->head;

    if (currPage == NULL) //The list is empty
    {
        reversedString[size] = '\0';
        return reversedString;
    }

    while (currPage != NULL) 
    {
        if (size == capacity) 
        {
            capacity = size + 1;
            reversedString = realloc(reversedString, capacity);
        }

        reversedString[size] = currPage->number;
        size++;

        currPage = currPage->next;
    }

    reversedString = realloc(reversedString, size + 1);
    reversedString[size] = '\0';

    //Reverse the string, so its human readable
    int reversedStringLen = strlen(reversedString);

    char *trueString = malloc(reversedStringLen + 1);

    for (int i = 0; i < reversedStringLen; i++) 
    {
        trueString[i] = reversedString[reversedStringLen - 1 - i];
    }

    trueString[reversedStringLen] ='\0';
    free(reversedString); 


    return trueString;
}
