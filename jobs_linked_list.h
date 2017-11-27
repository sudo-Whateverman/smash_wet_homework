/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   jobs_linked_list.h
 * Author: nick
 *
 * Created on November 27, 2017, 10:46 AM
 */

#ifndef JOBS_LINKED_LIST_H
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#define JOBS_LINKED_LIST_H
#define MAX_LINE_SIZE 80

typedef struct _job{
    int pid;
    int starting_time;
    char cmdLine[MAX_LINE_SIZE];
    int status; // 0 - running , 1 - stopped , 2 - Terminated
    struct _job* next;
} JOB_LL;

JOB_LL* createJOB(int pid, int starting_time, char* cmdLine, int status);
void print_jobs(JOB_LL* job_list_head);
void insert_job(JOB_LL* job_list_head, int pid, int starting_time, char* cmdLine, int status);
void delete_job(JOB_LL* job_list_head, int index);
void delete_job_by_pid(JOB_LL* job_list_head, int pid);
JOB_LL* pop_job(JOB_LL* job_list_head);
JOB_LL* pop_job_by_id(JOB_LL* job_list_head, int id);
JOB_LL* pop_job_by_pid(JOB_LL* job_list_head, int pid);



#endif /* JOBS_LINKED_LIST_H */
