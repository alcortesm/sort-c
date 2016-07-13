#include <stdlib.h>
#include <string.h>

#include "util.h"

char* strdup(const char* s) {
    size_t len = strlen(s);
    char* buf = malloc((len+1)*sizeof(char));
    if (!buf) {
        return NULL;
    }

    return strcpy(buf, s);
}

char* to_str(const int* a, int n) {
    UNUSED(a);
    UNUSED(n);
    return strdup("{}");
}
