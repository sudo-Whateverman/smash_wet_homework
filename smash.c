/*	smash.c
 main file. This file contains the main function of smash
 *******************************************************************/
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h> 
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "commands.h"
#include "signals.h"
#include "history.h"
#include "jobs_linked_list.h"
#define MAX_LINE_SIZE 80
#define MAXARGS 20



char* L_Fg_Cmd;
char lineSize[MAX_LINE_SIZE]; 
HISTORY history; //Initialize the history to avoid unwanted behavior
JOB_LL* jobs; //This represents the list of jobs. 
// A global signum to signame translation. 
char *sigtranslation_[]={"INVALID", "SIGHUP", "SIGINT", "SIGQUIT", "SIGILL", "SIGTRAP",
"SIGABRT", "SIGBUS", "SIGFPE", "SIGKILL", "SIGUSR1", "SIGSEGV", "SIGUSR2",
"SIGPIPE", "SIGALRM", "SIGTERM", "SIGSTKFLT", "SIGCHLD", "SIGCONT", "SIGSTOP",
"SIGTSTP", "SIGTTIN", "SIGTTOU", "SIGURG", "SIGXCPU", "SIGXFSZ", "SIGVTALRM",
"SIGPROF", "SIGWINCH", "SIGPOLL", "SIGPWR", "SIGSYS", NULL};

//**************************************************************************************
// function name: main
// Description: main function of smash. get command from user and calls command functions
//**************************************************************************************
int main(int argc, char *argv[])
{
    char cmdString[MAX_LINE_SIZE]; 	   
    (void)argc;
    (void)argv;
    
    //signal declarations
    //NOTE: the signal handlers and the function/s
    //that sets the handler should be found in siganls.c
    /* add your code here */
    
    // ^C signal, stop execution
    struct sigaction SIGINT_handler;
    SIGINT_handler.sa_handler = SIG_IGN;
    sigaction(SIGINT, &SIGINT_handler, NULL);
    
    // ^Z signal, go to sleep
    struct sigaction SIGTSTP_handler;
    SIGTSTP_handler.sa_handler = SIG_IGN;
    sigaction(SIGTSTP, &SIGTSTP_handler, NULL);

  
    
    /************************************/
    // Init globals 
    
    
    
//    L_Fg_Cmd =(char*)malloc(sizeof(char)*(MAX_LINE_SIZE+1));
//    if (L_Fg_Cmd == NULL) 
//        exit (-1); 
//    L_Fg_Cmd[0] = '\0';
    
    while (1)
    {
        printf("smash > ");
        fgets(lineSize, MAX_LINE_SIZE, stdin);
        strncpy(cmdString, lineSize, MAX_LINE_SIZE);    	
        cmdString[strlen(lineSize)-1]='\0';
        insert_history( &history, cmdString);
        // background command	
        if(!BgCmd(lineSize)) continue; 
        // perform a complicated Command
        if(!ExeComp(lineSize)) continue; 
        // built in commands
        ExeCmd(lineSize, cmdString);
        
        /* initialize for next line read*/
        lineSize[0]='\0';
        cmdString[0]='\0';
    }
    return 0;
}

//Project backlog:
//1) Add signal handlers. 
//2) Run all stuff in ExeComp in fg, waitpid f0r child.
//3) Run stuff in background f0r BgCmd
//4) Test background and foreground runs
//5) implement fg, bg, quit, jobs
//6) Test on virtual box of the course.
//7) Change & behavior to put in bg.
//8) add Stopped on status.

