#ifndef _SIGS_H
#define _SIGS_H
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "jobs_list.h"
extern int ctrl_z_count;
extern JOB_LIST jobs;
extern char *sigtranslation_[];
void catch_suspend(int sig_num);
void catch_int(int sig_num);
void placeholder(int sig_num);
void kill_and_run(int sig_num);

#endif

