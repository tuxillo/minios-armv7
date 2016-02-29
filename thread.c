#include <cpufunc.h>
#include <thread.h>

int nthreads;
unsigned char thread_stack[MAXTHREADS][STACKSIZE];
struct thread threads[MAXTHREADS];

struct thread *
thread_create(int(*func)(void *))
{
	int current = nthreads;

	if (nthreads >= MAXTHREADS) {
		kprintf("Maximum number of threads reached\n");
		return NULL;
	}

	threads[current].tid = current;
	threads[current].stack = thread_stack[current] + STACKSIZE - 1;
	threads[current].func = func;
	nthreads++;

	kprintf("[svc] Created thread %d\n", current);

	return &threads[current];
}

void
thread_destroy(struct thread *t)
{
}

void
run_threads(void)
{
	int current;

	if (nthreads == 0)
		return;

	for (;;) {
		for (current = 0; current < nthreads; current++) {
			/* Run thread function */
			_gouser(threads[current].func, threads[current].stack);
		}
	}
}
