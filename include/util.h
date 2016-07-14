#ifndef UTIL_H
#define UTIL_H

#ifndef UNUSED
#define UNUSED(x) (void)(x)
#endif

/* Returns a pointer to a newly allocated copy of s. */
char* strdup(const char* s);

/* Returns a pointer to a newly allocated string compossed
 * of the concatenation of s and the the formated string
 * format. Example:
 *
 *     strjoin("add", " %d %s", 2, "word");
 *
 *         returns the string "add 2 words"
 */
char* strjoin(const char* s, const char* format, ...);

/* Returns a pointer to a newly allocated string holding the string
 * representation of an array of ints, with the followin format:
 *
 * - an array with 0, 1, -7 is represented as "{0, 1, -7}"
 * - an array with a single 42 is represented as "{42}"
 * - a NULL is represented as "{}"
 */
char* to_str(const int* a, int n);

#endif /* UTIL_H */
