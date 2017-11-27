#ifndef _COMMANDS_H
#define _COMMANDS_H
#include <unistd.h> 
#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include "history.h"
#include "jobs_linked_list.h"
#include "signals.h"
#define MAX_LINE_SIZE 80
#define MAX_ARG 20
typedef enum { FALSE , TRUE } bool;
int ExeComp(char* lineSize);
int BgCmd(char* lineSize);
int ExeCmd(char* lineSize, char* cmdString);
int ExeExternal(char *args[MAX_ARG], int num_args);
extern JOB_LL *jobs;
extern char *sigtranslation_[];
extern struct sigaction SIGTSTP_handler;
extern struct sigaction SIGINT_handler;

#endif

