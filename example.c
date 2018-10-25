/* example.c
 * How to use nolibc_syscall.
 * 
 * Brandon Kammerdiener
 * October, 2018
 */

#include <sys/syscall.h>
#include <sys/stat.h>
#include <fcntl.h>

#include "nolibc_syscall.h"

#ifdef __APPLE__ /* MacOS is wack. */
    #define WRITE_SYSCALL (0x2000000 + SYS_write)
    #define OPEN_SYSCALL  (0x2000000 + SYS_open)
    #define CLOSE_SYSCALL (0x2000000 + SYS_close)
    #define EXIT_SYSCALL  (0x2000000 + SYS_exit)
#else
    #define WRITE_SYSCALL SYS_write
    #define OPEN_SYSCALL  SYS_open
    #define CLOSE_SYSCALL SYS_close
    #define EXIT_SYSCALL SYS_exit
#endif

int s_len(char * s) {
    int len = 0;

    while (*s++)
        len += 1;

    return len;
}

/* little wrappers */

long int myprint(int fd, char * s) {
    return nolibc_syscall(WRITE_SYSCALL, 3, fd, s, s_len(s));
}

int myopen(char * path, int flags, int mode) {
    return nolibc_syscall(OPEN_SYSCALL, 3, path, flags, mode);
}

int myclose(int fd) {
    return nolibc_syscall(CLOSE_SYSCALL, 1, fd);
}

void myexit(int status) {
    nolibc_syscall(EXIT_SYSCALL, 1, status);
}


int main(int argc, char ** argv);

/* our entry code */
void start() {
    /* The SVR4/i386 ABI says that the stack will have (among other things):
     *
     * 0(%rsp)                     argc
     * 8(%rsp)                     argv[0]
     */
    void    *sp;
    long int argc,
             status;
    char   **argv;

    /* get our frame address to extract argc and argv */
    sp = __builtin_frame_address(0) + 8;

    argc = *(long int*)sp;
    argv = (char**)(sp + 8);

    status = main(argc, argv);
    
    myexit(status);
}

/* the actual program */
int main(int argc, char ** argv) {
    int   i,
          fd;
    char *lazy_space,
         *usage;

    if (argc < 2) {
        usage = "usage: example FILE [...]\n";
        myprint(1, usage);
        return 1;
    }

    fd = myopen(argv[1], O_WRONLY | O_CREAT, S_IRWXU);

    lazy_space = "";

    for (i = 2; i < argc; i += 1) {
        myprint(fd, lazy_space);
        lazy_space = " ";
        myprint(fd, argv[i]);
    }

    myclose(fd);
    return 0;
}
