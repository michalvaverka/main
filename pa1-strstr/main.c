/**
    @filename:  main.c
    @author:    Michal Vaverka

    @description:
                Main file containing main methods and main function.

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
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include "linkedlist.h"


linkedList_t **getNeedles(linkedList_t *haystack, const char *needle, int *size);

linkedList_t *subList(page_t *from, int size);

int main(void) 
{
    linkedList_t *a = createListFromString("1231230981230129");

    int size;

    linkedList_t **foundNeedles = getNeedles(a, "123", &size);

    assert(size == 3);
    for (int i = 0; i < size; i++) 
    {
        char *needleString = toString(foundNeedles[i]);
        assert(!strcmp(needleString, "123"));
        free(needleString);
    }

    for (int i = 0; i < size; i++) clearList(foundNeedles[i]);
    
    free(foundNeedles);

    clearList(a);

    a = createListFromString("8880188822888");

    foundNeedles = getNeedles(a, "8", &size);
    
    assert(size == 9);
    for (int i = 0; i < size; i++) 
    {
        char *needleString = toString(foundNeedles[i]);
        assert(!strcmp(needleString, "8"));
        free(needleString);
    }

    for (int i = 0; i < size; i++) clearList(foundNeedles[i]);
    free(foundNeedles);

    clearList(a);

    a = createListFromString("9231847281902847231812981239318218751498931943131319473218491");

    foundNeedles = getNeedles(a, "31", &size);
    
    assert(size == 7);
    for (int i = 0; i < size; i++) 
    {
        char *needleString = toString(foundNeedles[i]);
        assert(!strcmp(needleString, "31"));
        free(needleString);
    }

    for (int i = 0; i < size; i++) clearList(foundNeedles[i]);
    free(foundNeedles);

    clearList(a);

    return 0;
}

linkedList_t **getNeedles(linkedList_t *haystack, const char *needle, int *size) 
{
    int capacity = 1;
    *size = 0;

    linkedList_t **ret = malloc(sizeof(linkedList_t *));

    page_t *currPage = haystack->head;
    page_t *needleStart = NULL;
    
    int index = 0;
    int needleSize = strlen(needle);

    while(currPage != NULL) 
    {
        if (needle[index] == '\0') 
        {
            if (capacity == *size) 
            {
                capacity++;
                ret = realloc(ret, capacity * sizeof(linkedList_t *));
            }

            ret[*size] = subList(needleStart, needleSize);
            (*size)++;

            index = 0;
            needleStart = NULL;
            continue;
        } else if (needle[index] == currPage->number + '0') 
        {
            if (needleStart == NULL) needleStart = currPage;

            index++;
        } else 
        {
            needleStart = NULL;
            index = 0;
        }

        currPage = currPage->next;
    }

    if (needleStart != NULL && needle[index] == '\0') 
    {
        if (capacity == *size) 
            {
                capacity++;
                ret = realloc(ret, capacity * sizeof(linkedList_t *));
            }

            ret[*size] = subList(needleStart, needleSize);
            (*size)++;
    }

    return ret;
}

linkedList_t *subList(page_t *from, int size) 
{
    linkedList_t *ret = (linkedList_t *) malloc(sizeof(linkedList_t));
    
    ret->head = NULL;
    
    for (int i = 0; i < size; i++) 
    {
        add(ret, createPage(from->number));
        from = from->next;
    }

    return ret;
}
