#ifndef ARRAY_H
#define ARRAY_H

typedef struct {
    int* a;
    int n;
} array;

array* array_new(int* a, int n);
array* array_clone(array* a);
array* array_random(int n);
void   array_free(array*);
int    array_size(array*);
char*  array_to_str(array*);
int    array_equals(array*, array*);

#endif /* ARRAY_H */
