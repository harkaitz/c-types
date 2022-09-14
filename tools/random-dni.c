#include "../types/spain/dni.h"
#include <sys/time.h>
#include <unistd.h>

int main (void) {
    dni_t dni;
    struct timeval tv;
    gettimeofday(&tv,NULL);
    srand(tv.tv_usec);
    dni_random(&dni);
    dni_fputs(dni, stdout);
    fputc('\n', stdout);
    return 0;
}
