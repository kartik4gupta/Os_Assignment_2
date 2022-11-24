#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <unistd.h>
#include <time.h>
#include <errno.h>
#include <pthread.h>


struct timespec A,B,C;

struct sched_param para;
pthread_t t1, t2, t3;

void sub_time(struct timespec st, struct timespec fn, struct timespec *gap)
{

    time_t secs;
    long nsecs;
    secs = fn.tv_sec - st.tv_sec;
    nsecs = fn.tv_nsec - st.tv_nsec;
    if (nsecs < 0){
        nsecs = nsecs + 1000000000;
        secs=secs-1;
    }
    gap->tv_sec=secs;
    gap->tv_nsec=nsecs;
}

void *count_A(void *arg)
{
    para.sched_priority = 0;
    pthread_setschedparam(t1, SCHED_OTHER, &para);
    unsigned long int i;
    struct timespec st, fn;
    int *thr_no = (int *)arg;
    
    unsigned long int upperLimit = 4294967295;
    clock_gettime(CLOCK_REALTIME, &st);
  int counterA=1;  
  while(counterA<=upperLimit){
        counterA++;
    }

    clock_gettime(CLOCK_REALTIME, &fn);
    sub_time(st, fn, &A);
    printf("Thread : %d - %ld.%ld\n", *thr_no, A.tv_sec, A.tv_nsec);
    return NULL;
}

void *count_B(void *arg)
{
    para.sched_priority = 25;
    pthread_setschedparam(t2, SCHED_RR, &para);
    int *thr_no = (int *)arg;
    struct timespec st, fn;
    clock_gettime(CLOCK_REALTIME, &st);
    unsigned long int i;
    unsigned long int UpperLt = 4294967295;
    int counterB=1;  
  while(counterB<=upperLimit){
        counterB++;
    }

    clock_gettime(CLOCK_REALTIME, &fn);
    sub_time(st, fn, &B);
    printf("Thread : %d - %ld.%ld\n", *thr_no, B.tv_sec, B.tv_nsec);
    return NULL;
}

void *count_C(void *arg)
{
    para.sched_priority = 51;
    pthread_setschedparam(t3, SCHED_FIFO, &para);
    int *thr_no = (int *)arg;
    struct timespec st, fn;
    clock_gettime(CLOCK_REALTIME, &st);

    unsigned long int i;
    unsigned long int UpperLt = 4294967295;
    int counterC=1;  
  while(counterC<=upperLimit){
        counterC++;
    }

    clock_gettime(CLOCK_REALTIME, &fn);
    sub_time(st, fn, &C);
    printf("Thread : %d - %ld.%ld\n", *thr_no, C.tv_sec, C.tv_nsec);
    return NULL;
}

int main(void)
{   
    int first = 1;
    int second = 2;
    int third = 3;
    pthread_create(&t1, NULL, count_A, (void *)&first);
    pthread_create(&t2, NULL, count_B, (void *)&second);
    pthread_create(&t3, NULL, count_C, (void *)&third);

    pthread_join(t3, NULL);
    pthread_join(t2, NULL);
    pthread_join(t1, NULL);

    return 0;
}
