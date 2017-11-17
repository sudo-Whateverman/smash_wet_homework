//		commands.c
//********************************************
#include "commands.h"

char PATH_[MAX_LINE_SIZE];
char PATH_prev[MAX_LINE_SIZE];
//********************************************
// function name: ExeCmd
// Description: interprets and executes built-in commands
// Parameters: pointer to jobs, command string
// Returns: 0 - success,1 - failure
//**************************************************************************************
int ExeCmd(void* jobs, char* lineSize, char* cmdString)
{
    char* cmd; 
    char* args[MAX_ARG];
    char pwd[MAX_LINE_SIZE];
    char* delimiters = " \t\n";  
    int i = 0, num_arg = 0;
    bool illegal_cmd = FALSE;
    cmd = strtok(lineSize, delimiters);
    if (cmd == NULL)
        return 0; 
    args[0] = cmd;
    for (i=1; i<MAX_ARG; i++)
    {
        args[i] = strtok(NULL, delimiters); 
        if (args[i] != NULL) 
            num_arg++;  // TODO : check each fun for correct num_arg
        
    }
    /*************************************************/
    // Built in Commands PLEASE NOTE NOT ALL REQUIRED
    // ARE IN THIS CHAIN OF IF COMMANDS. PLEASE ADD
    // MORE IF STATEMENTS AS REQUIRED
    /*************************************************/
    if (!strcmp(cmd, "cd") ) 
    {   
        // This is the path_previous and path swapping place.
        // The path variables must be global in scope in order to be changed
        // This may lead to a buggy implement, will be fixed if enough time
        // is given. for now it works TODO: refactor.
        if (num_arg==1)
        {
            if (!strcmp(args[1], "-") )
            {
                strncpy(PATH_, PATH_prev, MAX_LINE_SIZE);
            }
            else
            {
                strncpy(PATH_, args[1], MAX_LINE_SIZE);
            }
            getcwd(PATH_prev, MAX_LINE_SIZE);
            
            if (chdir(PATH_)==-1)
            {
                printf("\"%s\" - path not found\n", PATH_);
                return -1;
            }
            else
            {
                return 0;
            }
        }
        else
        {
            illegal_cmd = TRUE;    
        }
        
    } 
    
    /*************************************************/
    else if (!strcmp(cmd, "pwd")) 
    {
        if (num_arg==0)
        {
            getcwd(pwd, MAX_LINE_SIZE);
            printf("%s\n",pwd);
            return 0; 
        }
        else
        {
            illegal_cmd = TRUE;
        }
    }
    
    /*************************************************/
    else if (!strcmp(cmd, "mkdir"))
    {
        if (num_arg == 1)
        {
            struct stat st = {0};
            if (stat(args[1], &st) == -1) 
            {
                mkdir(args[1], 0700);
            }
            return 0;                
        }
        else
        {
            illegal_cmd = TRUE;
        }
    }
    /*************************************************/
    
    else if (!strcmp(cmd, "jobs")) 
    {
        
    }
    /*************************************************/
    
    else if (!strcmp(cmd, "mv")) 
    {
        if (num_arg == 2)
        {
            if (!rename(args[1], args[2])){
                printf("%s has been renamed %s\n", args[1], args[2]);
            }
            else
            {
                perror ("The following error occurred");
            }
        }
        else
        {
            illegal_cmd = TRUE;
        }
    }
    /*************************************************/
    else if (!strcmp(cmd, "showpid")) 
    {
        if (num_arg==0)
        {
            int smash_pid;
            smash_pid = getpid();
            printf("smash pid is %d\n", smash_pid);
            return 0;                
        }
        else
        {
            illegal_cmd = TRUE;
        }
    }
    /*************************************************/
    else if (!strcmp(cmd, "fg")) 
    {
        
    } 
    /*************************************************/
    else if (!strcmp(cmd, "bg")) 
    {
        
    }
    /*************************************************/
    else if (!strcmp(cmd, "history"))
    {
        if (num_arg==0)
        {
            print_hist(&history);
        }
        else
        {
            illegal_cmd = TRUE;
        }
    } 
    /*************************************************/
    else if (!strcmp(cmd, "quit"))
    {
        
    } 
    /*************************************************/
    else 
    {
        ExeExternal(args, cmdString, num_arg);
        return 0;
    }
    if (illegal_cmd == TRUE)
    {
        printf("smash error: > \"%s\"\n", cmdString);
        return 1;
    }
    return 0;
}
//**************************************************************************************
// function name: ExeExternal
// Description: executes external command
// Parameters: external command arguments, external command string
// Returns: void
//**************************************************************************************
int ExeExternal(char *args[MAX_ARG], char* cmdString, int num_args)
{
    int pID;
    int status;
    args[num_args + 1] = NULL;
    switch(pID = fork()) 
    {
        case -1: 
            // TODO : Add error code here
            perror ("The following error occurred");
            break;
            
        case 0 :
            setpgrp();
            if (execvp( args[0], args))
            {
                perror ("The following error occurred");
            }
            exit(0);
            break;
            
        default:
            
            wait(&status);
            return status;
            
    }
    return 0;
}
//**************************************************************************************
// function name: ExeComp
// Description: executes complicated command
// Parameters: command string
// Returns: 0- if complicated -1- if not
//**************************************************************************************
int ExeComp(char* lineSize)
{
    if ((strstr(lineSize, "|")) || (strstr(lineSize, "<")) || (strstr(lineSize, ">")) || (strstr(lineSize, "*")) || (strstr(lineSize, "?")) || (strstr(lineSize, ">>")) || (strstr(lineSize, "|&")))
    {
	char* args[5];
        int pID;
        int status;
        args[0] = "/bin/sh";
        args[1] = "-f";
        args[2] = "-c";
        args[3] = lineSize;
        args[3][strlen(lineSize)-1]='\0';
        args[4] = NULL;
        switch(pID = fork()) 
        {
            case -1: 
                perror ("The following error occurred");
                break;
            case 0 :
                setpgrp();
                if (!execv( args[0], args))
                {
                    perror ("The following error occurred");
                }
                exit(0);
                break;
                
            default:
                wait(&status);
                return 0;
                
        }
        return 0;
    } 
    return -1;
}
//**************************************************************************************
// function name: BgCmd
// Description: if command is in background, insert the command to jobs
// Parameters: command string, pointer to jobs
// Returns: 0- BG command -1- if not
//**************************************************************************************
int BgCmd(char* lineSize, void* jobs)
{
    
    char* Command;
    char* delimiters = " \t\n";
    char *args[MAX_ARG];
    if (lineSize[strlen(lineSize)-2] == '&')
    {
        lineSize[strlen(lineSize)-2] = '\0';
        int pID;
        int status;
        int i, num_arg;
        Command = strtok(lineSize, delimiters);
        if (Command == NULL)
            return 0; 
        args[0] = Command;
        for (i=1; i<MAX_ARG; i++)
        {
            args[i] = strtok(NULL, delimiters); 
            if (args[i] != NULL) 
                num_arg++;  // TODO : check each fun for correct num_arg
        }
        args[num_arg + 1] = NULL;
        switch(pID = fork()) 
        {
            case -1: 
                // TODO : Add error code here
                perror ("The following error occurred");
                break;
                
            case 0 :
                setpgrp();
                if (execvp( args[0], args))
                {
                    perror ("The following error occurred");
                }
                exit(0);
                break;
                
            default:
                break;
                
        }
        return 0;
    }
    return -1;
}
    
