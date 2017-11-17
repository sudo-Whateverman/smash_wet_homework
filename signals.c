// signals.c
// contains signal handler funtions
// contains the function/s that set the signal handlers

/*******************************************/
/* Name: handler_cntlc
 Synopsis: handle the Control-C */
#include "signals.h"

void catch_suspend(int sig_num) {
    sigset_t mask_set; /* used to set a signal masking set. */
    sigset_t old_set; /* used to store the old mask set. */
    sigfillset(&mask_set);
    sigprocmask(SIG_SETMASK, &mask_set, &old_set);
    pause();
    fflush(stdout);
    sigprocmask(SIG_SETMASK,&old_set, &mask_set);
}

void catch_int(int sig_num) {
    printf("Got that ^C\n");
}

