#include "test_util.h"

#ifndef UNUSED
#define UNUSED(x) (void)(x)
#endif

int main(int argc, char** argv) {
    UNUSED(argc);
    UNUSED(argv);

    return test_util();
}
