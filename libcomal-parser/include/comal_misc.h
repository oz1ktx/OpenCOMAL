#ifndef COMAL_MISC_H
#define COMAL_MISC_H

#include "comal_ast.h"

void my_printf(int stream, int newline, char *s, ...);
void fatal(char *s, ...);
void *my_reverse(void *root);
int exp_list_of_nums(struct exp_list *root);
char *exp_cmd(struct expression *exp);
struct comal_line *stat_dup(struct comal_line *stat);

#endif
