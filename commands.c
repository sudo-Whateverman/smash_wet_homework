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
int ExeCmd(char* lineSize, char* cmdString)
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
    // Parse CmdLine to tokens saved in args.
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
                // This is the regular path change behaviour, take argument
                // and make it the path.
                strncpy(PATH_, args[1], MAX_LINE_SIZE);
            }
            // update path_prev.
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
            /* Get the pathname of the current working directory,
             and put it in SIZE bytes of BUF.  Returns NULL if the
             directory couldn't be determined or SIZE was too small.
             If successful, returns BUF.  In GNU, if BUF is NULL,
             an array is allocated with `malloc'; the array is SIZE
             bytes long, unless SIZE == 0, in which case it is as
             big as necessary.  */
            if (!getcwd(pwd, MAX_LINE_SIZE))
            {
                perror("The following error occurred");
                return -1;
            }
            else{
                printf("%s\n",pwd);
                return 0; 
            }
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
            // Check that the directory isn't present.
            if (stat(args[1], &st) == -1) 
            {
                if(!mkdir(args[1], 0700))
                {
                    perror("The following error occurred");
                    return -1;
                }
                else
                {
                    return 0;                

                }
            }
            else
            {
                printf("%s is already existing", args[1]);
                return 0;
            }
        }
        else
        {
            illegal_cmd = TRUE;
        }
    }
    /*************************************************/
    else if (!strcmp(cmd, "mv")) 
    {
        if (num_arg == 2)
        {
            // in order to mv. just use a rename. the data stays where it was
            // just gets pointed from another place.
            if (!rename(args[1], args[2])){
                printf("%s has been renamed %s\n", args[1], args[2]);
                return 0;
            }
            else
            {
                perror ("The following error occurred");
                return -1;
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
    // The difference from fg to bg would be a blocking wait or not.
    // Since both ar = 0 and 1 are similiar, I should refactor the function.
    else if (!strcmp(cmd, "fg")) 
    {
        int status, endID;
        if (num_arg==0)
        {
            JOB job = jobs.jobs[jobs.front-1];
            printf("‫‪signal‬‬ ‫‪SIGCONT‬‬ ‫‪was‬‬ ‫‪sent‬‬ ‫‪to‬‬ ‫‪pid‬‬ %d", job.pid);
            // using kill to send signals.
            kill( job.pid, SIGCONT);
            // check to see if process has returned.
            while ( endID!= job.pid){
                endID = waitpid( job.pid, &status, WNOHANG);
                if (endID == -1) 
                {/* error calling waitpid       */
                    perror("waitpid error");
                    exit(EXIT_FAILURE);
                }
            }
            return status;
        }
        // similar to the no arguments case, but this time the job chosen
        // is given by args[1], which should be checked that can be parsed.
        // if atoi gives a "wrong" number it will be off the job list index
        // and thus no job will be selected.
        else if (num_arg==1)
        {
            int index = atoi(args[1]);
            JOB job = jobs.jobs[index];
            printf("‫‪signal‬‬ ‫‪SIGCONT‬‬ ‫‪was‬‬ ‫‪sent‬‬ ‫‪to‬‬ ‫‪pid‬‬ %d", job.pid);
            kill( job.pid, SIGCONT);
            while ( endID!= job.pid){
                endID = waitpid( job.pid, &status, WNOHANG);
                if (endID == -1) 
                {/* error calling waitpid       */
                    perror("waitpid error");
                    exit(EXIT_FAILURE);
                }
            }
            return status;
        }
        else
        {
            illegal_cmd = TRUE;
        }
        
    } 
    /*************************************************/
    else if (!strcmp(cmd, "bg")) 
    {
        // Same as fg, but don't wait on the process.
        if (num_arg==0)
        {
            JOB job = jobs.jobs[jobs.front];
            kill( job.pid, SIGCONT);            
            printf("‫‪signal‬‬ ‫‪SIGCONT‬‬ ‫‪was‬‬ ‫‪sent‬‬ ‫‪to‬‬ ‫‪pid‬‬ %d", job.pid);
            return 0;
        }
        else if (num_arg==1)
        {
            int index = atoi(args[1]);
            JOB job = jobs.jobs[index];
            printf("‫‪signal‬‬ ‫‪SIGCONT‬‬ ‫‪was‬‬ ‫‪sent‬‬ ‫‪to‬‬ ‫‪pid‬‬ %d", job.pid);            
            kill( job.pid, SIGCONT);
            return 0;
        }
        else
        {
            illegal_cmd = TRUE;
        }
    }
    /*************************************************/
    else if (!strcmp(cmd, "history"))
    {
        if (num_arg==0)
        {
            // see documentation at helper function history.c
            print_hist(&history);
        }
        else
        {
            illegal_cmd = TRUE;
        }
    } 
    /*************************************************/
    else if (!strcmp(cmd, "jobs"))
    {
        if (num_arg==0)
        {
            // see documentation at helper function job_list.c
            print_jobs(&jobs);
        }
        else
        {
            illegal_cmd = TRUE;
        }
    } 
    /*************************************************/
    else if (!strcmp(cmd, "quit"))
    {
        if (num_arg==0)
        {
            // if no arguments passed, just call to exit and let
            // system handle the killing.
            exit(0);
        }
        else if (num_arg==1 && !strcmp(args[1], "kill"))
        {
            JOB job;
            int status;
            for (int i=0; i<jobs.front; i++){
                if (job.status != 2){
                    job = jobs.jobs[i];
                    printf("[%d] %s - Sending SIGTERM...", i, job.cmdLine);
                    kill(job.pid, SIGTERM);
                    fflush(stdout);
                    sleep(5);
                    int endID = waitpid( job.pid, &status, WNOHANG);
                    if (endID != job.pid)
                    {
                        printf("(5 sec passed) Sending SIGKILL...");
                        fflush(stdout);
                        kill(job.pid, SIGKILL);
                    }
                    printf("Done.\n");
                }
            }
            fflush(stdout);
            exit(0);
        }
        else
        {
            illegal_cmd = TRUE;
        }
    } 
        /*************************************************/
    else if (!strcmp(cmd, "kill"))
    {
        if (num_arg==2)
        {
            JOB job;
            char signal_name[MAX_LINE_SIZE];
            int index, signal_;
            index = atoi(args[2]);
            strncpy(signal_name, &args[1][1], strlen(args[1])-1); // dirty Hack
            // basicaly it truncates the string exluding the '-' sign and then
            // passes the string to parse.
            signal_ = atoi(signal_name);
            job = jobs.jobs[index];
            if (job.pid == 0){
                printf("‫‪smash‬‬ ‫‪error:‬‬ ‫>‬ ‫‪kill‬‬ ‫‪job‬‬ %d ‫‪job‬‬ ‫‪does‬‬ ‫‪not‬‬ ‫‪exist‬‬\n", index);
                return 1;
            }
            else if (kill(job.pid, signal_))
            {
               printf("‫‪smash‬‬ ‫‪error:‬‬ ‫>‬ ‫‪kill‬‬ ‫‪job‬‬ %d ‫‪cannot‬‬ ‫‪send‬‬ ‫‪signal‬‬\n", index);
               return 1;
            }
            else
            {
                printf("‫‪signal‬‬ %s ‫‪was‬‬ ‫‪sent‬‬ ‫‪to‬‬ ‫‪pid‬‬ %d\n",
                        sigtranslation_[signal_], job.pid );               
                return 0;
            }
        }
        else
        {
            illegal_cmd = TRUE;
        }
    } 
    /*************************************************/
    else 
    {
        ExeExternal(args, num_arg);
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
// Parameters: external command arguments, external command string,
// number of arguments of command
// Returns: 0- on success -return value of child - if child fails.
//**************************************************************************************
int ExeExternal(char *args[MAX_ARG], int num_args)
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
// Parameters: command string // FIX IN OTHER PLACES
// Returns: 0- BG command -1- if not
//**************************************************************************************
int BgCmd(char* lineSize)
{
    
    char* Command;
    char* delimiters = " \t\n";
    char *args[MAX_ARG];
    if (lineSize[strlen(lineSize)-2] == '&')
    {
        lineSize[strlen(lineSize)-2] = '\0';
        int pID;
        int i, num_arg;
        JOB bg_job;
        strncpy(bg_job.cmdLine, lineSize, MAX_LINE_SIZE);
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
                kill(pID, SIGSTOP);  // TO DO : delete this from here.
                bg_job.pid = pID;
                bg_job.starting_time = time(NULL);
                bg_job.status = 0;
                printf("Started %s at pid %d\n", bg_job.cmdLine, bg_job.pid );
                insert_job(&jobs, bg_job);
                break;
                
        }
        return 0;
    }
    return -1;
}

