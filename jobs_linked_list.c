/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   jobs_linked_list.c
 * Author: nick
 * 
 * Created on November 27, 2017, 10:46 AM
 */

#include "jobs_linked_list.h"
//JOB_LL head = (JOB_LL) malloc(sizeof(JOB_LL));

JOB_LL* createJOB(int pid, int starting_time, char* cmdLine, int status)
{
    JOB_LL* temp; // declare a node
    temp = (JOB_LL*)malloc(sizeof(JOB_LL)); // allocate memory using malloc()
    temp->pid = pid;
    temp->starting_time = starting_time;
    strncpy(temp->cmdLine,cmdLine,MAX_LINE_SIZE);
    temp->next = NULL;// make next point to NULL
    temp->status = status;
    return temp;//return the new node
}
void insert_job(int pid, int starting_time, char* cmdLine, int status)
{
    JOB_LL *p, *temp;
    temp = createJOB(pid, starting_time, cmdLine, status);
    if(jobs == NULL){
        jobs = temp;     //when linked list is empty
    }
    else{
        p  = jobs;//assign head to p 
        while(p->next != NULL){
            p = p->next;//traverse the list until p is the last node.The last node always points to NULL.
        }
        p->next = temp;//Point the previous last node to the new node created.
    }
}
void delete_job(int index){
    JOB_LL *p, *temp;
    p = jobs;
    int i=0;
    if (index == 0){
        jobs = jobs-> next;
        free(p);
    }
    else{
        while(p!= NULL){
            if( i != index){
                temp =p;
                p= p->next;
                i++;
            }
            else{
                temp->next = p->next;
                free(p);
                p = temp->next;
                break;
            }
        }
    }
}
void delete_job_by_pid(int pid){
    JOB_LL *p, *temp;
    p = jobs;
    if (jobs->pid == pid && pid != 0){
        jobs = jobs-> next;
        free(p);
    }
    else{
        while(p!= NULL){
            if( p->pid != pid){
                temp =p;
                p= p->next;
            }
            else{
                temp->next = p->next;
                free(p);
                p = temp->next;
                break;
            }
        }
    }
}
void print_jobs(void)
{
    JOB_LL *p = jobs;
    int status;
    int index;
    while (p != NULL){
        if ((p->pid != 0 )&& (waitpid(p->pid, &status, WNOHANG) != 0))
        {
            p = p -> next;
            delete_job(index);
            // if the job is dead, delete the job from the list.
        }
        else
        {
            int time_elapsed = time( NULL ) - p->starting_time;
            // elapsed seconds is self time from epoch deducted from
            // current time since epoch.
            if (p->status == 1)
            {
                printf("[%d] %s : %d %d secs (Stopped) \n",
                        index, p->cmdLine, p->pid, time_elapsed );
            }
            else
            {
                printf("[%d] %s : %d %d secs \n"
                        , index, p->cmdLine, p->pid, time_elapsed );
            }
            p = p->next;
            index ++;
        }
        
    }
}

JOB_LL* pop_job(void){
    JOB_LL *temp,*p;
    p = jobs;
    temp = jobs;
    while(p != NULL){
        temp = p;
        p = p->next;
    }
    return temp;
}
JOB_LL* pop_job_by_id(int id){
    JOB_LL *temp,*p;
    p = jobs;
    temp = jobs;
    int i=0;
    if (id==0){
        return jobs;
    }
    else{
        while(i != id){
            temp = p;
            p = p->next;
            i++;
        }
        return temp;
    }
    return NULL;
}
JOB_LL* pop_job_by_pid(int pid){
    JOB_LL *temp,*p;
    p = jobs;
    temp = jobs;
    if (jobs->pid== pid){
        return jobs;
    }
    else{
        while(temp->pid != pid){
            temp = p;
            p = p->next;
        }
        return temp;
    }
    return NULL;
}