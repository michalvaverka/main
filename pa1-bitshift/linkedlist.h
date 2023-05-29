/**
    @filename:  linkedlist.h
    @author:    Michal Vaverka

    @description:
                Header file for linkedlist file containing list representation and functions to manipulate it.

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
                    2) The project borrowing this code IS NOT commercial, NOR accademical,
                    3) The creator of project borrowing this code will NOT present this project to a superior figure in his organization.

                Any usage in compliance with rules listed above is allowed.

                Michal Vaverka, 2023.
*/
#ifndef LINKEDL
#define LINKEDL

typedef struct {
    char number;
    void *next;
} page_t;

typedef struct {
    page_t *head;
} linkedList_t;

page_t *createPage(char number);

/* Adds a member to the beginning of the list */
void push(linkedList_t *list, page_t *toPush);

/* Adds a member to the end of the list */
void add(linkedList_t *list, page_t *toAdd);

void clearList(linkedList_t *list);

void printList(linkedList_t *list);

/* Create string representing linked list in human-readable order */
linkedList_t *createLinkedListString(const char *string);

/* Create linked list from string */
char *linkedListToString(linkedList_t *toString);

#endif
