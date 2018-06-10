#ifndef VECTOR_H
#define VECTOR_H

#define VECTOR_MAX_EXPAND_STEP 250

typedef enum {
	VECTOR_STATUS_OK,
	VECTOR_STATUS_ERR_ALLOC,
	VECTOR_STATUS_ERR_UNDERFLOW
} VECTOR_STATUS;

typedef struct {
	long size;
	long idx;
	char **data;
} vector_str;

VECTOR_STATUS vector_init_str(vector_str *vector);
VECTOR_STATUS vector_push_str(vector_str *vector, const char *src);
VECTOR_STATUS vector_prepend_str(vector_str *vector, const char *src);
static VECTOR_STATUS vector_auto_expand_str(vector_str *vector);
long vector_search_str(vector_str *vector, const char *src);
VECTOR_STATUS vector_pop(vector_str *vector);
static VECTOR_STATUS vector_auto_shrink_str(vector_str *vector);
void vector_destroy_str(vector_str *vector);

typedef struct {
	unsigned int size;
	unsigned int idx;
	int *data;
} vector_int;

#endif