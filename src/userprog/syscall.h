#ifndef USERPROG_SYSCALL_H
#define USERPROG_SYSCALL_H

#include "process.h"

void syscall_init (void);
void check_address(void * addr);
tid_t exec(const char* file);
void exit(int status);
int wait(tid_t pid);
int write(int fd, const void * buffer, unsigned size);
int read(int fd, void * buffer, unsigned size);
int fibonacci(int n);
int max_of_four_int(int a, int b, int c, int d);

#endif /* userprog/syscall.h */
