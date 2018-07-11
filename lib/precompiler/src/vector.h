#ifndef VECTOR_H
#define VECTOR_H
#include <stdbool.h>

#define VECTOR_MAX_EXPAND_STEP 250

typedef enum {
	VECTOR_STATUS_OK,
	VECTOR_STATUS_ERR_ALLOC,
	VECTOR_STATUS_ERR_UNDERFLOW
} VECTOR_STATUS;

struct vector_str {
	long size;
	long idx;
	char **data;
};

VECTOR_STATUS vector_init_str(struct vector_str *vector);
VECTOR_STATUS vector_push_str(struct vector_str *vector, const char *src);
VECTOR_STATUS vector_prepend_str(struct vector_str *vector, const char *src);
static VECTOR_STATUS vector_auto_expand_str(struct vector_str *vector);
long vector_search_str(struct vector_str *vector, const char *src);
VECTOR_STATUS vector_pop_str(struct vector_str *vector);
VECTOR_STATUS vector_pop_front_str(struct vector_str *vector);
static VECTOR_STATUS vector_auto_shrink_str(struct vector_str *vector);
void vector_destroy_str(struct vector_str *vector);

//<DYNAMIC_ENTRIES>

#endif
