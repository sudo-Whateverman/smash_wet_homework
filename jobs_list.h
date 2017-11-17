/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   jobs_list.h
 * Author: nick
 *
 * Created on November 17, 2017, 7:53 PM
 */

#ifndef JOBS_LIST_H
#define JOBS_LIST_H
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#define MAX_JOBS_LIST 80
#define MAX_LINE_SIZE 80

typedef struct _job{
    int pid;
    int starting_time;
    char cmdLine[MAX_LINE_SIZE];
    int status; // 0 - running , 1 - stopped , 2 - Terminated
} JOB;

typedef struct _job_list{
    int front;
    int rear;
    int size;
    JOB jobs[MAX_JOBS_LIST];
} JOB_LIST;
extern JOB_LIST jobs;

void print_jobs(JOB_LIST* job_list_);
void insert_job(JOB_LIST* job_list_, JOB job_);
#endif /* JOBS_LIST_H */


//How it works in linux:
//nick@Nicole-AI:~/study/os_course/smash/smash$ python test.py > a.out &
//[1] 29718
//nick@Nicole-AI:~/study/os_course/smash/smash$ python test.py > b.out &
//[2] 29721
//nick@Nicole-AI:~/study/os_course/smash/smash$ python test.py > c.out &
//[3] 29722
//nick@Nicole-AI:~/study/os_course/smash/smash$ jobs
//[1]   Running                 python test.py > a.out &
//[2]-  Running                 python test.py > b.out &
//[3]+  Running                 python test.py > c.out &
//nick@Nicole-AI:~/study/os_course/smash/smash$ kill 2
//bash: kill: (2) - Operation not permitted
//nick@Nicole-AI:~/study/os_course/smash/smash$ jobs
//[1]   Running                 python test.py > a.out &
//[2]-  Running                 python test.py > b.out &
//[3]+  Running                 python test.py > c.out &
//nick@Nicole-AI:~/study/os_course/smash/smash$ man jobs
//No manual entry for jobs
//nick@Nicole-AI:~/study/os_course/smash/smash$ jobs kill 2
//bash: jobs: kill: no such job
//[2]-  Running                 python test.py > b.out &
//nick@Nicole-AI:~/study/os_course/smash/smash$ jobs
//[1]   Running                 python test.py > a.out &
//[2]-  Running                 python test.py > b.out &
//[3]+  Running                 python test.py > c.out &
//nick@Nicole-AI:~/study/os_course/smash/smash$ kill 29721
//nick@Nicole-AI:~/study/os_course/smash/smash$ jobs
//[1]   Running                 python test.py > a.out &
//[2]-  Terminated              python test.py > b.out
//[3]+  Running                 python test.py > c.out &
//nick@Nicole-AI:~/study/os_course/smash/smash$ jobs
//[1]-  Running                 python test.py > a.out &
//[3]+  Running                 python test.py > c.out &
//nick@Nicole-AI:~/study/os_course/smash/smash$ jobs
//[1]-  Running                 python test.py > a.out &
//[3]+  Running                 python test.py > c.out &
//nick@Nicole-AI:~/study/os_course/smash/smash$ jobs
//[1]-  Running                 python test.py > a.out &
//[3]+  Running                 python test.py > c.out &
//nick@Nicole-AI:~/study/os_course/smash/smash$ jobs
//[1]-  Running                 python test.py > a.out &
//[3]+  Running                 python test.py > c.out &
//nick@Nicole-AI:~/study/os_course/smash/smash$ python test.py > d.out &
//[4] 29727
//nick@Nicole-AI:~/study/os_course/smash/smash$ jobs
//[1]   Running                 python test.py > a.out &
//[3]-  Running                 python test.py > c.out &
//[4]+  Running                 python test.py > d.out &
//nick@Nicole-AI:~/study/os_course/smash/smash$ kill 29727
//nick@Nicole-AI:~/study/os_course/smash/smash$ kill 29722
//[4]+  Terminated              python test.py > d.out
//nick@Nicole-AI:~/study/os_course/smash/smash$ jobs
//[1]-  Running                 python test.py > a.out &
//[3]+  Terminated              python test.py > c.out
//nick@Nicole-AI:~/study/os_course/smash/smash$ jobs
//[1]+  Running                 python test.py > a.out &
//nick@Nicole-AI:~/study/os_course/smash/smash$ python test.py > e.out &
//[2] 29736
//nick@Nicole-AI:~/study/os_course/smash/smash$ kill 29736
//nick@Nicole-AI:~/study/os_course/smash/smash$ kill 29718
//[2]+  Terminated              python test.py > e.out
//nick@Nicole-AI:~/study/os_course/smash/smash$ jobs
//[1]+  Terminated              python test.py > a.out
//nick@Nicole-AI:~/study/os_course/smash/smash$ jobs
