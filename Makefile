CC ?= gcc
LD ?= ld

CFLAGS  := -nostdlib -fno-stack-protector -O3 
LDFLAGS := -L. -lnolibc_syscall

UNAME_S := $(shell uname -s)

PREFIX  :=

# MacOS is wack.
ifeq ($(UNAME_S),Darwin)
	LDFLAGS += -static
	LDFLAGS += -macosx_version_min $(shell system_profiler SPSoftwareDataType | grep 'System Version' | awk '{ print $$4; }')
	PREFIX  += _
endif

all: libnolibc_syscall.a example

example: libnolibc_syscall.a example.o
	$(LD) -e $(PREFIX)start example.o $(LDFLAGS) -o example

libnolibc_syscall.a: nolibc_syscall.o
	ar rvs libnolibc_syscall.a nolibc_syscall.o

example.o: example.c
	$(CC) $(CFLAGS) -c example.c

nolibc_syscall.o: nolibc_syscall.c
	$(CC) $(CFLAGS) -fPIC -c nolibc_syscall.c

clean:
	rm -f example example.o libnolibc_syscall.a nolibc_syscall.o
