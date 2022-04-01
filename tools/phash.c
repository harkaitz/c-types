#include "../include/str/phash.h"
int main(int argc, const char *argv[]) {
    uint64_t hash = 0;
    for(int i=1;i<argc;i++) {
        hash = phash(hash, "s", argv[i]);
    }
    printf("%" PRIu64 "\n",hash);
    return 0;
}
