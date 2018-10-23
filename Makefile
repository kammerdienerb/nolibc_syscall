CC ?= gcc
LD ?= ld

CFLAGS  := -nostdlib -O3
LDFLAGS := -L. -lnolibc_syscall

UNAME_S := $(shell uname -s)

ifeq ($(UNAME_S),Darwin)
	CFLAGS  += -fno-stack-protector
	LDFLAGS += -lSystem -macosx_version_min $(shell system_profiler SPSoftwareDataType | grep 'System Version' | awk '{ print $$4; }')
endif

all: libnolibc_syscall.a example

example: libnolibc_syscall.a example.o
	$(LD) $(LDFLAGS) -e _main example.o -o example

libnolibc_syscall.a: nolibc_syscall.o
	ar rvs libnolibc_syscall.a nolibc_syscall.o

example.o: example.c
	$(CC) $(CFLAGS) -c example.c

nolibc_syscall.o: nolibc_syscall.c
	$(CC) $(CFLAGS) -fPIC -c nolibc_syscall.c

clean:
	rm -f example libnolibc_syscall.a nolibc_syscall.o