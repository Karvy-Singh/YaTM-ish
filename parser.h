#ifndef parser_h
#define parser_h

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "parser.h"

static bool id_seen_before(int window_id, int *id_array, int size);
void top_used_windows(char *top_names[3], int top_ids[3]);

#endif
