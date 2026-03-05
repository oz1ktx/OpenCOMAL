#ifndef COMAL_BASE_H
#define COMAL_BASE_H

#include <stdlib.h>
#include <stdio.h>

#include "comal_constants.h"
#include "comal_messages.h"
#include "comal_functions.h"
#include "comal_memory.h"
#include "comal_ast.h"

#define PRIVATE static
#define PUBLIC

#define COMMAND(x) (32767 - (x))

#endif
