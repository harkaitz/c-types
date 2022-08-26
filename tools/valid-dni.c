#include "../types/spain/dni.h"

int main (int _argc, char const *_argv[]) {

    dni_t dni;
    if (_argc == 1) {
        fprintf(stdout, "Usage: valid-dni DNI\n");
        return 0;
    } else if (dni_parse(&dni, _argv[1])) {
        dni_fputs(dni, stdout);
        fputc('\n', stdout);
        return 0;
    } else {
        fprintf(stderr, "Invalid DNI: %s\n", _argv[1]);
        return 1;
    }
    
}
