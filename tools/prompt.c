//bin/true && exec hcc "$0" "$@"
#include "../include/io/prompt.h"
int main (int argc, const char *argv[]) {

    const char *opts, *prompt;
    char buffer[512] = {0}; char *line;
    
    if (argc == 1) {
        opts   = "";
        prompt = NULL;
    } else if (argv[1][0] == '-') {
        opts   = argv[1]+1;
        prompt = argv[2];
    } else {
        opts   = "";
        prompt = argv[1];
    }

    if (strchr(opts, 'h')) {
        printf("Usage: prompt [-p] [PROMPT] > RESPONSE\n");
        return 1;
    }
    
    
    if (strchr(opts, 'p')) {
        line = prompt_fgetpw(prompt, buffer, sizeof(buffer)-1);
    } else {
        line = prompt_fgets(prompt, buffer, sizeof(buffer)-1);
    }
    if (line == NULL) {
        return 1;
    }

    printf("%s\n", buffer);
    
}
