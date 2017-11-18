/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "history.h"
int temp;
char element[MAX_LINE_SIZE];

//********************************************
// function name: print_hist
// Description: prints all history from a round buffer of entries
// Parameters: pointer to history global
// Returns: void
//********************************************
void print_hist(HISTORY* history_)
{
    temp = history_->front;
    if (history_->size!=0)
    {
        while(temp!=history_->rear)
        {
            printf("%s \n", history_->entries[temp]);
            temp = (temp + 1)% MAX_HISTORY_SIZE;
        } 
    }
}

//********************************************
// function name: insert_history
// Description: inserts a line of cmdline into global object list
// Parameters: pointer to history, cmdline that was sent
// Returns: void
//********************************************
void insert_history(HISTORY* history_, char* element)
{
    if ((history_->size)<MAX_HISTORY_SIZE-1)
    {
        history_->size ++;
        strncpy(history_->entries[history_->rear], element, MAX_LINE_SIZE);
        history_->rear = (history_->rear + 1 )%MAX_HISTORY_SIZE;
    }
    else
    {
        // When history entries become larger than size. we just use
        // the buffer in a circular manner to pop last and push the first
        // at the same time.
        strncpy(history_->entries[history_->rear], element, MAX_LINE_SIZE);
        history_->rear = (history_->rear + 1 )%MAX_HISTORY_SIZE;
        history_->front = (history_->front + 1)%MAX_HISTORY_SIZE;
    }
}
 

