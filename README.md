# nolibc_syscall

There are only two ways in which POSIX system calls are exposed: assembly, and the C standard library wrappers. _nolibc\_syscall_ is a small C library designed to allow the use of system calls on x86_64 without the need to link with the C standard library. This can be useful when trying to create very small executables or limit dependencies. At the very least, it was fun to write.

## Building ##
`make`

## Using ##
`#include "nolibc_syscall.h"` in your C file.

Link with `-lnolibc_syscall`.

See _example.c_ for example usage. The _Makefile_ can provide insight into building applications that don't rely on _libc_.
