#ifndef COMAL_PROGRAM_H
#define COMAL_PROGRAM_H

#include "comal_ast.h"

void prog_addline(struct comal_line *line);
int prog_del(struct comal_line **root, long from, long to, int mainprog);
long prog_highest_line(void);
void prog_total_scan(void);
void prog_new(void);
void prog_load(char *fn);
void prog_run(void);

#endif
