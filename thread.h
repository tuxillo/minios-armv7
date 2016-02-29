#ifndef _THREAD_H_
#define _THREAD_H_

#define MAXTHREADS	16
#define STACKSIZE	4096
extern int nthreads;

struct thread *thread_create(int(*func)(void *));

struct thread {
	int tid;
	unsigned char *stack;
	int (*func)(void *);
};

#endif /* _THREAD_H_ */
