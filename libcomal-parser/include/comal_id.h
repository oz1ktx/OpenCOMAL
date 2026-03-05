#ifndef COMAL_ID_H
#define COMAL_ID_H

#include "comal_ast.h"

int id_eql(struct id_rec *id1, struct id_rec *id2);
struct id_rec *id_search(char *id);
void id_reset(void);

#endif
