#ifndef SORT_H
#define SORT_H

#include "array.h"

typedef int sort_fn(array*);
sort_fn sort_bubble;
sort_fn sort_merge_nspace;
sort_fn sort_quick;

#endif /* SORT_H */
