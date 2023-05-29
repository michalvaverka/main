/**
    @filename:  main.c
    @author:    Michal Vaverka

    @description:
                Main file containing main-functionality functions (could be another file) and main function itself.

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
#include <stdbool.h>
#include <ctype.h>
#include <assert.h>
#include <string.h>

#include "linkedlist.h"

#define CHARASCIDIF 55

/* Deepcopy of a linked list */
linkedList_t *copyLinkedList(linkedList_t *toCopy) 
{
    linkedList_t *ret = (linkedList_t *) malloc(sizeof(linkedList_t));
    ret->head = NULL;

    page_t *currPage = toCopy->head;

    while (currPage != NULL) 
    {
        add(ret, createPage(currPage->number));

        currPage = currPage->next;
    }

    return ret;
}

int getDecFromHex(char number) 
{
    int ret;

    if (isnumber(number)) ret = number - '0';
    else if(number > 70 || number < 65) return -1;
    else ret = number - CHARASCIDIF;

    return ret;
}

int getHexFromDec(int number) 
{
    int ret;

    if (number < 10) ret = number + '0';
    else ret = number + CHARASCIDIF;

    return ret;
}

int getRemainder(int number) { return number / 16; }

/* Checks whether a given list ends with a zero or not */
    /* Could be done way simpler by providing a tail in list, however that
        was specifically prohibited. */
bool checkForZeroes(linkedList_t *list) 
{
    bool endsWithZero = false;

    page_t *currPage = list->head;

    while (currPage != NULL) 
    {
        if (currPage->number == '0') endsWithZero = true;
        else endsWithZero = false;

        currPage = currPage->next;
    }

    return endsWithZero;
}


/* Performs a left shift by shiftCount places on a number represented in list */
linkedList_t *shiftLeft(linkedList_t *list, int shiftCount) 
{
    if (list == NULL || checkForZeroes(list)) return NULL;

    linkedList_t *ret = copyLinkedList(list);
    
    page_t *currPage;
    int currNum;
    int remainder = 0;

    for (int i = 0; i < shiftCount; i++) 
    {
        currPage = ret->head;

        while (currPage != NULL) 
        {
            currNum = getDecFromHex(currPage->number);

            if (currNum == -1)
            {
                clearList(ret);
                return NULL;
            }
            
            currNum *= 2;               //left shift corresponds to *2
            currNum += remainder;       //we add "overflowed" value from the previous round

            remainder = getRemainder(currNum);  //extract anything that will overflow

            currNum %= 16;                      //get what remains in this "domain"             

            currPage->number = getHexFromDec(currNum);

            currPage = currPage->next;
        }

        if (remainder) add(ret, createPage(getHexFromDec(remainder))), remainder = 0; // if theres still some overflowing at the end
                                                                                        // we must add a new element
    }

    return ret;
}

/* Helper function to actually performs one right shift, putting it in another function is a bit inconsistent design choice*/
/* However, it is calling itself recursively */
int rightShifter(page_t *currPage) 
{
    if (currPage->next == NULL)         //end of recursive call
    {
        int count = getDecFromHex(currPage->number);
        int ret = count % 2;
        count /= 2;
        currPage->number = getHexFromDec(count);

        if (currPage->number == 0 + '0')    // omit zeros at the beggining and signal removal
        {
            ret -= 2;
            free(currPage);
        }

        return ret;
    } else 
    {
        int add = rightShifter(currPage->next); // recursive call on next
        int count = getDecFromHex(currPage->number);
        int ret = count % 2;
        count /= 2;

        if (add < 0) currPage->next = NULL, add += 2;

        if (add) count += 8;

        currPage->number = getHexFromDec(count);

        return ret;
    }

}

/* Performs a specified number of right shifts */
linkedList_t *shiftRight(linkedList_t *list, int shiftCount) 
{
    if (list == NULL || checkForZeroes(list)) return NULL;

    linkedList_t *ret = copyLinkedList(list);

    for (int i = 0; i < shiftCount; i++) 
    {
        if(rightShifter(ret->head) < 0) 
        {
            ret->head = NULL;
            break;
        }
    }

    return ret;
}

/* Could be aside in a test function */
int main (int argc, char * argv [])
{
    linkedList_t *result = NULL;
    linkedList_t *a = NULL;
    char *resultString = NULL;
    
    a = createLinkedListString("123");
    result = shiftLeft(a, 1);

    resultString = linkedListToString(result);

    assert(!strcmp(resultString, "246"));
    free(resultString);

    clearList(a), clearList(result);

    a = createLinkedListString("1AF");

    result = shiftLeft(a, 3);

    resultString = linkedListToString(result);

    assert(!strcmp(resultString, "D78"));
    free(resultString);

    clearList(a), clearList(result);

    a = createLinkedListString("1D45C");

    result = shiftLeft(a, 5);

    resultString = linkedListToString(result);

    assert(!strcmp(resultString, "3A8B80"));
    free(resultString);

    clearList(a), clearList(result);

    a = createLinkedListString("0WA");

    result = shiftLeft(a, 12);

    assert(result == NULL);

    clearList(a);

    a = NULL;

    result = shiftLeft(a, 1);
    assert(result == NULL);

    a = createLinkedListString("222");

    result = shiftRight(a, 1);

    resultString = linkedListToString(result);

    assert(!strcmp(resultString, "111"));
    free(resultString);

    clearList(result);

    result = shiftRight (a, 2);

    resultString = linkedListToString(result);

    assert(!strcmp(resultString, "88"));
    free(resultString);

    clearList(result);

    result = shiftRight (a, 10);

    resultString = linkedListToString(result);

    assert(!strcmp(resultString, ""));
    free(resultString);

    clearList(result), clearList(a);

    a = createLinkedListString("FF12B");

    result = shiftRight(a, 1);

    resultString = linkedListToString(result);

    assert(!strcmp(resultString, "7F895"));
    free(resultString);

    clearList(result), clearList(a);

    return 0;
}
