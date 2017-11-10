//		commands.c
//********************************************
#include "commands.h"

char PATH_[MAX_LINE_SIZE];
char PATH_prev[MAX_LINE_SIZE];
//HISTORY history;
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
	bool illegal_cmd = FALSE; // illegal command
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
                return 0; //TODO: add error handling
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
            //print_history(history);
	} 
        /*************************************************/
	else if (!strcmp(cmd, "quit"))
	{
   		
	} 
	/*************************************************/
	else // external command
	{
 		ExeExternal(args, cmdString);
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
void ExeExternal(char *args[MAX_ARG], char* cmdString)
{
	int pID;
    	switch(pID = fork()) 
	{
    		case -1: 
					// Add your code here (error)
			printf("error using fork please try again");
                        break;
                        /* 
					your code
					*/
        	case 0 :
                	// Child Process
               		setpgrp();
				
                        break;
			        // Add your code here (execute an external command)
					
					/* 
					your code
					*/
			
		default:
                	// Add your code here
                        printf("This is external mode; could not find path");
                        execv(cmdString, args);
                        return;
			/* 
        		your code
			*/
	}
}
//**************************************************************************************
// function name: ExeComp
// Description: executes complicated command
// Parameters: command string
// Returns: 0- if complicated -1- if not
//**************************************************************************************
int ExeComp(char* lineSize)
{
	char ExtCmd[MAX_LINE_SIZE+2];
	char *args[MAX_ARG];
    if ((strstr(lineSize, "|")) || (strstr(lineSize, "<")) || (strstr(lineSize, ">")) || (strstr(lineSize, "*")) || (strstr(lineSize, "?")) || (strstr(lineSize, ">>")) || (strstr(lineSize, "|&")))
    {
		// Add your code here (execute a complicated command)
					
		/* 
		your code
		*/
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
		// Add your code here (execute a in the background)
					
		/* 
		your code
		*/
		
	}
	return -1;
}

