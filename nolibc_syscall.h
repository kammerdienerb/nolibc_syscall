/*
 * nolibc_syscall.h
 *
 * x86_64 system call interface that is not a part
 * of or dependent upon libc.
 *
 * Brandon Kammerdiener
 * October, 2018
 */

#ifndef _NOLIBC_SYSCALL_H_
#define _NOLIBC_SYSCALL_H_

#include <signal.h>

typedef void (*sigaction_handler_t)(int);

#ifdef __cplusplus
extern "C" {
#endif

long int nolibc_syscall(long int n, int n_args, ...);

sigaction_handler_t* nolibc_syscall_sigaction_sa_handler(struct sigaction* act);
int* nolibc_syscall_sigaction_sa_flags(struct sigaction* act);

#ifdef __cplusplus
}
#endif

#endif
