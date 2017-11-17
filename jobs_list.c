/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   jobs_list.c
 * Author: nick
 * 
 * Created on November 17, 2017, 7:53 PM
 */

#include "jobs_list.h"


void insert_job(JOB_LIST* job_list_, JOB job_)
{
    if ((job_list_->size)<MAX_JOBS_LIST)
    {
        //        printf("Will add job to list\n");
        //        printf("job_list_->rear %d\n"
        //                "job_list_->front %d\n"
        //                "job_list_->size %d\n",
        //                job_list_->rear ,job_list_->front, job_list_->size);
        job_list_->jobs[job_list_->front] = job_;        
        job_list_->size ++;
        job_list_->front++;
        
    }
    else
    {
        printf("Cannot add more jobs, the queue is too long\n");
    }
}

void print_jobs(JOB_LIST* job_list_)
{
    JOB job;
    int status;
    for (int i=0; i<job_list_->size; i++){
        job = job_list_->jobs[i];
        if (waitpid(job.pid, &status, WNOHANG) != 0)
        {
            job_list_->jobs[i].status = 2;
                    
        }
        else
        {
            int time_elapsed = time( NULL ) - job.starting_time;
            printf("[%d] %s : %d %d secs \n", i, job.cmdLine, job.pid, time_elapsed );
        }
        
    }
}