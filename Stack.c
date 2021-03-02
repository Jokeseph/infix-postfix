#include "Stack.h"

/******
 * In this file, provide all of the definitions of the stack functions as described in stack.h.
 *
 * ****/
#define TRUE 1
#define FALSE 0

Stack newStack(int maximumStackSize)
{
    StackImp* newStack = (StackImp*)malloc(sizeof(StackImp));
    newStack->count = 0;
    newStack->maxSize = maximumStackSize;
    newStack->stackElements = (Element*)malloc(maximumStackSize * sizeof(Element));

    return newStack;
}



void freeStack(Stack s)
{
	free(s->stackElements);
	free(s);
}

void push(Stack s, Element e)
{
    if(s->maxSize <= s->count)
    {
        s->maxSize *= 2;
        s->stackElements = realloc(s->stackElements, s->maxSize * sizeof(int));
    }

    s->stackElements[s->count] = e;
    s->count++;
}

Element pop(Stack s)
{
    if(isEmpty(s) == TRUE)
    {
        printf("Error : stack is empty\n");
    }
    else
    {
        return s->stackElements[s->count--];
    }
}


int isEmpty(Stack s)
{
    if(s->count == 0)
    {
        return TRUE;
    }
    else
    {
        return FALSE;
    }
}

Element topElement(Stack s)
{
    if(isEmpty(s) == TRUE)
    {
        printf("Error: stack is empty\n");

    }
    else
    {
        return s->stackElements[s->count - 1];
    }
}