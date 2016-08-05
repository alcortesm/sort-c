#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdarg.h>

#include "util.h"

char* strdup(const char* s) {
    size_t len = strlen(s);
    char* buf = malloc((len+1)*sizeof(char));
    if (!buf) {
        return NULL;
    }

    return strcpy(buf, s);
}

char* strjoin(const char* src, const char* format, ...) {
    if (!src || !format) {
        return NULL;
    }

    va_list args;
    va_start(args, format);
    int argslen = vsnprintf(NULL, 0, format, args);
    if (argslen < 0) {
        return strdup(src);
    }

    size_t srclen = 0;
    if (src) {
        srclen = strlen(src);
    }

    char* ret = malloc(srclen + argslen + 1);
    if (!ret) {
        return NULL;
    }

    strcpy(ret, src);

    va_start(args, format);
    int nw = vsprintf(ret+srclen, format, args);
    if (nw < 0) {
        return NULL;
    }

    return ret;
}

char* to_str(const int* a, int n) {
    if (!a) {
        return strdup("{}");
    }

    char* ret = strdup("{");
    if (!ret) {
        return NULL;
    }

    const char* sep = "";
    int i;
    char* together;
    for (i=0; i<n; i++) {
        together = strjoin(ret, sep);
        if (!together) {
            free(ret);
            return NULL;
        }
        free(ret);
        ret = together;

        together = strjoin(ret, "%d", a[i]);
        if (!together) {
            free(ret);
            return NULL;
        }
        free(ret);
        ret = together;

        sep = ", ";
    }

    together = strjoin(ret, "}");
    if (!together) {
        free(ret);
        return NULL;
    }
    free(ret);
    ret = together;

    return ret;
}
