#include <sys/types.h>
#include <sys/stat.h>

void _exit(int status) {
    while (1) {}
}

int _read(int file, char *ptr, int len) {
    return 0;
}

int _write(int file, char *ptr, int len) {
    return len;
}

int _close(int file) {
    return -1;
}

int _lseek(int file, int ptr, int dir) {
    return 0;
}

int _sbrk(int incr) {
    return 0;
}

int _fstat(int file, struct stat *st) {
    return 0;
}

int _isatty(int file) {
    return 1;
}

int _kill(int pid, int sig) {
    return 0;
}

int _getpid(void) {
    return 1;
}
