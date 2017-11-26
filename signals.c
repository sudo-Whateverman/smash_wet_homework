// signals.c
// contains signal handler funtions
// contains the function/s that set the signal handlers

/*******************************************/
/* Name: handler_cntlc
 Synopsis: handle the Control-C */
#include "signals.h"
#include "jobs_list.h"

void catch_suspend(int sig_num) {
    sigset_t mask_set; /* used to set a signal masking set. */
    sigset_t old_set; /* used to store the old mask set. */
    sigfillset(&mask_set);
    sigprocmask(SIG_SETMASK, &mask_set, &old_set);
    /* print the current Ctrl-Z counter */
    printf("\n\n Ctrl-Z pressed\n\n %d\n", sig_num);
    fflush(stdout);
    sigprocmask(SIG_SETMASK,&old_set, &mask_set);

}

void catch_int(int sig_num) {
    printf("Got that ^C\n%d\n", sig_num);
}

void placeholder(int sig_num) {
    printf("Got a signal number %d\n", sig_num);
}

void kill_and_run(int signum){
    JOB job;
    job = jobs.jobs[jobs.front -1];
    kill(job.pid, signum);
    printf("‫‪signal‬‬ %s ‫‪was‬‬ ‫‪sent‬‬ ‫‪to‬‬ ‫‪pid‬‬ %d\n",
            sigtranslation_[signum], job.pid ); 
    if (signum == 2)
    {
        jobs.jobs[jobs.front -1].status = 2;
    }
    else if(signum == 20)
    {
        jobs.jobs[jobs.front -1].status = 1;
    }
    else
    {
        exit(0);
    }
    signal(signum, kill_and_run);
}

