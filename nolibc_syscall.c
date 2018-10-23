/*
 * nolibc_syscall.c
 *
 * x86_64 system call interface that is not a part
 * of or dependent upon libc.
 *
 * Brandon Kammerdiener
 * October, 2018
 */

#include <stdarg.h>

long int nolibc_syscall0(long int n) {
    long int r;
    __asm__ volatile (
    "syscall\n\t"
    : "=a" (r)
    : "0" (n)
    : "memory", "cc", "r11", "cx");

    return r;
}

long int nolibc_syscall1(long int n, long int arg1) {
    long int r;
    register long int a1 __asm__ ("rdi") = arg1;
    __asm__ volatile (
    "syscall\n\t"
    : "=a" (r)
    : "0" (n), "r" (a1)
    : "memory", "cc", "r11", "cx");

    return r;
}

long int nolibc_syscall2(long int n, long int arg1, long int arg2) {
    long int r;
    register long int a2 __asm__ ("rsi") = arg2;
    register long int a1 __asm__ ("rdi") = arg1;
    __asm__ volatile (
    "syscall\n\t"
    : "=a" (r)
    : "0" (n), "r" (a1), "r" (a2)
    : "memory", "cc", "r11", "cx");

    return r;
}

long int nolibc_syscall3(long int n, long int arg1, long int arg2, long int arg3) {
    long int r;
    register long int a3 __asm__ ("rdx") = arg3;
    register long int a2 __asm__ ("rsi") = arg2;
    register long int a1 __asm__ ("rdi") = arg1;
    __asm__ volatile (
    "syscall\n\t"
    : "=a" (r)
    : "0" (n), "r" (a1), "r" (a2), "r" (a3)
    : "memory", "cc", "r11", "cx");

    return r;
}

long int nolibc_syscall4(long int n, long int arg1, long int arg2, long int arg3, long int arg4) {
    long int r;
    register long int a4 __asm__ ("r10") = arg4;
    register long int a3 __asm__ ("rdx") = arg3;
    register long int a2 __asm__ ("rsi") = arg2;
    register long int a1 __asm__ ("rdi") = arg1;
    __asm__ volatile (
    "syscall\n\t"
    : "=a" (r)
    : "0" (n), "r" (a1), "r" (a2), "r" (a3), "r" (a4)
    : "memory", "cc", "r11", "cx");

    return r;
}

long int nolibc_syscall5(long int n, long int arg1, long int arg2, long int arg3, long int arg4, long int arg5) {
    long int r;
    register long int a5 __asm__ ("r8")  = arg5;
    register long int a4 __asm__ ("r10") = arg4;
    register long int a3 __asm__ ("rdx") = arg3;
    register long int a2 __asm__ ("rsi") = arg2;
    register long int a1 __asm__ ("rdi") = arg1;
    __asm__ volatile (
    "syscall\n\t"
    : "=a" (r)
    : "0" (n), "r" (a1), "r" (a2), "r" (a3), "r" (a4), "r" (a5)
    : "memory", "cc", "r11", "cx");

    return r;
}

long int nolibc_syscall6(long int n, long int arg1, long int arg2, long int arg3, long int arg4, long int arg5, long int arg6) {
    long int r;
    register long int a6 __asm__ ("r9")  = arg6;
    register long int a5 __asm__ ("r8")  = arg5;
    register long int a4 __asm__ ("r10") = arg4;
    register long int a3 __asm__ ("rdx") = arg3;
    register long int a2 __asm__ ("rsi") = arg2;
    register long int a1 __asm__ ("rdi") = arg1;
    __asm__ volatile (
    "syscall\n\t"
    : "=a" (r)
    : "0" (n), "r" (a1), "r" (a2), "r" (a3), "r" (a4), "r" (a5), "r" (a6)
    : "memory", "cc", "r11", "cx");

    return r;
}

long int nolibc_syscall(long int n, int n_args, ...) {
    va_list args;
    long int r, a1, a2, a3, a4, a5, a6;

    va_start(args, n_args);

    switch (n_args) {
        case 0:
            r = nolibc_syscall0(n);
            break;
        case 1:
            r = nolibc_syscall1(n, va_arg(args, long int));
            break;
        case 2:
            a1 = va_arg(args, long int);
            a2 = va_arg(args, long int);
            r = nolibc_syscall2(n, a1, a2);
            break;
        case 3:
            a1 = va_arg(args, long int);
            a2 = va_arg(args, long int);
            a3 = va_arg(args, long int);
            r = nolibc_syscall3(n, a1, a2, a3);
            break;
        case 4:
            a1 = va_arg(args, long int);
            a2 = va_arg(args, long int);
            a3 = va_arg(args, long int);
            a4 = va_arg(args, long int);
            r = nolibc_syscall4(n, a1, a2, a3, a4);
            break;
        case 5:
            a1 = va_arg(args, long int);
            a2 = va_arg(args, long int);
            a3 = va_arg(args, long int);
            a4 = va_arg(args, long int);
            a5 = va_arg(args, long int);
            r = nolibc_syscall5(n, a1, a2, a3, a4, a5);
            break;
        case 6:
            a1 = va_arg(args, long int);
            a2 = va_arg(args, long int);
            a3 = va_arg(args, long int);
            a4 = va_arg(args, long int);
            a5 = va_arg(args, long int);
            a6 = va_arg(args, long int);
            r = nolibc_syscall6(n, a1, a2, a3, a4, a5, a6);
            break;
        default:
            r = -1;
    }

    va_end(args);

    return r;
}
