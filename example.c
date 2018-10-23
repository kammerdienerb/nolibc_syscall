/* example.c
 * How to use nolibc_syscall.
 * 
 * Brandon Kammerdiener
 * October, 2018
 */

#include <sys/syscall.h>
#include <fcntl.h>

#include "nolibc_syscall.h"

#ifdef __APPLE__ /* MacOS is wack. */
    #define WRITE_SYSCALL (0x2000000 + SYS_write)
    #define OPEN_SYSCALL  (0x2000000 + SYS_open)
    #define CLOSE_SYSCALL (0x2000000 + SYS_close)
#else
    #define WRITE_SYSCALL SYS_write
    #define OPEN_SYSCALL  SYS_open
    #define CLOSE_SYSCALL SYS_close
#endif

int s_len(char * s) {
    int len = 0;

    while (*s++)
        len += 1;

    return len;
}

void print(int fd, char * s) {
    nolibc_syscall(WRITE_SYSCALL, 3, fd, s, s_len(s));
}

int main(int argc, char ** argv) {
    int   i,
          fd;
    char *lazy_space,
         *usage;

    if (argc < 2) {
        usage = "usage: example FILE [...]\n";
        print(1, usage);
        return 1;
    }

    fd = nolibc_syscall(OPEN_SYSCALL, 3, argv[1], O_WRONLY | O_CREAT, S_IRWXU);

    lazy_space = "";

    for (i = 2; i < argc; i += 1) {
        print(fd, lazy_space);
        lazy_space = " ";
        print(fd, argv[i]);
    }

    return 0;
}
