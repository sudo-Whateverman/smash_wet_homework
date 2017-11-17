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
#define MAX_LINE_SIZE 80
#define MAXARGS 20


typedef struct _job{
    int pid;
    int starting_time;
    char cmdLine[MAX_LINE_SIZE];
} JOB;
char* L_Fg_Cmd;
JOB* jobs = NULL; //This represents the list of jobs. Please change to a preferred type (e.g array of char*)
char lineSize[MAX_LINE_SIZE]; 
HISTORY history; //Initialize the history to avoid unwanted behavior
int ctrl_z_count;


//**************************************************************************************
// function name: main
// Description: main function of smash. get command from user and calls command functions
//**************************************************************************************
int main(int argc, char *argv[])
{
    char cmdString[MAX_LINE_SIZE]; 	   
    
    
    //signal declarations
    //NOTE: the signal handlers and the function/s
    //that sets the handler should be found in siganls.c
    /* add your code here */
    
    // ^C signal, stop execution
    struct sigaction SIGINT_handler;
    SIGINT_handler.sa_handler = &catch_int;
    sigaction(SIGINT, &SIGINT_handler, NULL);
    
    // ^Z signal, go to sleep
    struct sigaction SIGTSTP_handler;
    SIGTSTP_handler.sa_handler = &catch_suspend;
    sigaction(SIGTSTP, &SIGTSTP_handler, NULL);
    
    // Quit the shell
    struct sigaction SIGQUIT_handler;
    SIGQUIT_handler.sa_handler = &catch_int;
    sigaction(SIGQUIT, &SIGQUIT_handler, NULL);
    
    // Resume foreground.
    struct sigaction SIGCONT_handler;
    SIGCONT_handler.sa_handler = &catch_int;
    sigaction(SIGCONT, &SIGCONT_handler, NULL);
    
    
    /************************************/
    // Init globals 
    
    
    
    L_Fg_Cmd =(char*)malloc(sizeof(char)*(MAX_LINE_SIZE+1));
    if (L_Fg_Cmd == NULL) 
        exit (-1); 
    L_Fg_Cmd[0] = '\0';
    
    while (1)
    {
        printf("smash > ");
        fgets(lineSize, MAX_LINE_SIZE, stdin);
        strcpy(cmdString, lineSize);    	
        cmdString[strlen(lineSize)-1]='\0';
        insert_history( &history, cmdString);
        // background command	
        if(!BgCmd(lineSize, jobs)) continue; 
        // perform a complicated Command
        if(!ExeComp(lineSize)) continue; 
        // built in commands
        ExeCmd(jobs, lineSize, cmdString);
        
        /* initialize for next line read*/
        lineSize[0]='\0';
        cmdString[0]='\0';
    }
    return 0;
}

//Project backlog:
//1) Add signal handlers. 
//2) Run all stuff in ExeComp in fg, waitpid fr child.
//3) Run stuff in background fpr BgCmd
//4) Test background and foreground runs
//5) implement fg, bg, quit, jobs
//6) Test on virtual box of the course.

