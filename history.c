/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include "history.h"
int temp;
HISTORY history;
char element[MAX_LINE_SIZE];

void print_history(HISTORY history)
{
    temp = history.front;
    for(int i=0; (temp!=history.rear); i++)
    {
        temp = ((history.front + i)%MAX_HISTORY_SIZE);
        printf("%s \n", history.entries[temp]);
    }
}

void insert_history(HISTORY history, char element)
{
    history.rear = (history.rear + 1 )%MAX_HISTORY_SIZE;
    if (history.rear == history.front){
        history.front = (history.front + 1)%MAX_HISTORY_SIZE;
        strncpy(history.entries[history.rear], element, MAX_LINE_SIZE);
    }
}
 
// TODO : fix later

