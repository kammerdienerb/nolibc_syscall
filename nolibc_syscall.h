/*
 * nolibc_syscall.h
 *
 * x86_64 system call interface that is not a part
 * of or dependent upon libc.
 *
 * Brandon Kammerdiener
 * October, 2018
 */

long int nolibc_syscall(long int n, int n_args, ...);
