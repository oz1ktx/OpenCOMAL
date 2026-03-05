#ifndef COMAL_STRING_UTILS_H
#define COMAL_STRING_UTILS_H

#include "comal_ast.h"

char *my_strdup(int pool, char *s);
char *my_strcpy(char *to, char *from);
void strupr(char *s);
void strlwr(char *s);
void remove_trailing(char *s, char *trailing, char *subst);
int str_cmp(struct string *s1, struct string *s2);
struct string *str_make(int pool, char *s);
struct string *str_make2(int pool, long len);
struct string *str_cat(struct string *s1, struct string *s2);
long str_search(struct string *needle, struct string *haystack);
struct string *str_cpy(struct string *s1, struct string *s2);
struct string *str_partcpy(struct string *s1, struct string *s2, long from, long to);
struct string *str_partcpy2(struct string *s1, struct string *s2, long from, long to);
struct string *str_dup(int pool, struct string *s);
struct string *str_maxdup(int pool, struct string *s, long n);
void str_extend(int pool, struct string **s, long newlen);

#endif
