#include "threading.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

// Optional: use these functions to add debug or error prints to your application
#define DEBUG_LOG(msg,...) printf("threading: " msg "\n" , ##__VA_ARGS__)
#define ERROR_LOG(msg,...) printf("threading ERROR: " msg "\n" , ##__VA_ARGS__)

void* threadfunc(void* thread_param)
{
    DEBUG_LOG("\nENTER: threadfunc\n");

    struct thread_data* thread_func_args = (struct thread_data *) thread_param;

    /* wait */
    DEBUG_LOG("waiting to obtain:  %d [ms]", thread_func_args->wait_to_obtain_ms);
    usleep(1000 * thread_func_args->wait_to_obtain_ms);

    /* obtain mutex */
    int rc = pthread_mutex_lock(thread_func_args->mutex);

    thread_func_args->thread_complete_success = (0 == rc);

    /* wait */
    DEBUG_LOG("waiting to release:  %d [ms]", 
                thread_func_args->wait_to_release_ms);
    usleep(1000 * thread_func_args->wait_to_release_ms);

    /* release mutex */
    pthread_mutex_unlock(thread_func_args->mutex);

    pthread_exit (thread_param);
}


bool start_thread_obtaining_mutex(pthread_t *thread, pthread_mutex_t *mutex,
                                  int wait_to_obtain_ms, int wait_to_release_ms)
{
    DEBUG_LOG("\nENTER: start_thread_obtaining_mutex\n");

    int rc = 0;

    /* allocate memory for thread_data */
    struct thread_data * tdata = (struct thread_data *) malloc(
                                                    sizeof(struct thread_data));
    bool b_success = (NULL != tdata);

    if (b_success)
    {
        tdata->mutex = mutex;
        tdata->wait_to_obtain_ms  = wait_to_obtain_ms;
        tdata->wait_to_release_ms = wait_to_release_ms;
        tdata->thread_complete_success = false;
        rc = pthread_create(thread, NULL, threadfunc, tdata);
        b_success = (0 == rc);
    }

    if (NULL != tdata)
    {
//        free(tdata);
    }

    DEBUG_LOG("\nEXIT %d: start_thread_obtaining_mutex\n", b_success);
    return (b_success);
}

