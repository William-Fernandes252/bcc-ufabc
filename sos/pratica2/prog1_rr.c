#define _GNU_SOURCE
#include <sched.h>
#include <stdio.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <sys/times.h>
#include <unistd.h>

#define CSEC_STEP 25            /* CPU centiseconds between messages */

int useCPU() {
    int prevStep = 0;
    int prevSec = 0;
    for (;;) {
        struct tms tms;
        if (times(&tms) == -1)
            printf("times error.");
        int cpuCentisecs = (tms.tms_utime + tms.tms_stime) * 100 /
                           sysconf(_SC_CLK_TCK);

        if (cpuCentisecs >= prevStep + CSEC_STEP) {
            prevStep += CSEC_STEP;
            printf("(PID %ld) cpu=%0.2f\n", (long) getpid(),
                    cpuCentisecs / 100.0);
        }

        if (cpuCentisecs > 500)         /* Terminate after 3 seconds */
            break;
      }

}

int useCPU2() {
  int n = 0;
  while(1) {
    n++;
    if (!(n % 100000000)) {
      printf("PID %ld FIFO running (n=%d)\n",(long) getpid(),n);
    }
  }
}


int main(int argc, char **argv)
{
  setbuf(stdout, NULL);               /* Disable buffering of stdout */
     
  /* Confine all processes to a single CPU, so that the processes
       won't run in parallel on multi-CPU systems. */


  printf("Setting SCHED_RR and priority to %d\n",atoi(argv[1]));
  struct sched_param param;
  param.sched_priority = atoi(argv[1]);
  if (sched_setscheduler(0, SCHED_RR, &param) !=0) {
     printf("Failed to set the scheduler\n");
  }
  int pid = fork();
  if (pid==0) {
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(&set);

    if (sched_setaffinity(getpid(), sizeof(set), &set) == -1)
      printf("sched_setaffinity error.");
    useCPU();
  } else {
    cpu_set_t set;
    CPU_ZERO(&set);
    CPU_SET(2, &set);

    if (sched_setaffinity(getpid(), sizeof(set), &set) == -1)
      printf("sched_setaffinity error.");
    useCPU();
  }
}
