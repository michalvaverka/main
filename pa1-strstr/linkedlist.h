/**
    @filename:  linkedlist.h
    @author:    Michal Vaverka

    @description:
                Header file of list datatypes and functions.

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
                    2) The project borrowing this code IS NOT commercial, NOR accademical,
                    3) The creator of project borrowing this code will NOT present this project to a superior figure in his organization.

                Any usage in compliance with rules listed above is allowed.

                Michal Vaverka, 2023.
*/
#ifndef LINKEDL
#define LINKEDL

#include <stdio.h>

typedef struct {
    int number;
    void *next;
} page_t;

typedef struct {
    page_t *head;
} linkedList_t;

page_t *createPage(int number);

linkedList_t *createListFromString(const char *string);

void push(linkedList_t *list, page_t *toPush);

void add(linkedList_t *list, page_t *toAdd);

void clearList(linkedList_t *list);

void printList(linkedList_t *list);

char *toString(linkedList_t *list);

#endif
