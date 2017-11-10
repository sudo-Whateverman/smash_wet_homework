/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   history.h
 * Author: nick
 *
 * Created on November 10, 2017, 11:52 PM
 */

#ifndef HISTORY_H
#define HISTORY_H
#define MAX_LINE_SIZE 80
#define MAX_HISTORY_SIZE 5

typedef struct _history{
    int front;
    int rear;
    char entries[MAX_HISTORY_SIZE][MAX_LINE_SIZE];
} HISTORY;
HISTORY history;
void print_history(HISTORY history);
void insert_history(HISTORY history, char* element);
#ifdef __cplusplus
extern "C" {
#endif




#ifdef __cplusplus
}
#endif

#endif /* HISTORY_H */

