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

long int nolibc_syscall(long int n, int n_args, ...);

#endif
