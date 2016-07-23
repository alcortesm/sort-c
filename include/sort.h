#ifndef SORT_H
#define SORT_H

typedef int* (*sort_fn)(int*, int);

int* sort_bubble(int*, int);
int* sort_merge_nspace(int*, int);

#endif /* SORT_H */
