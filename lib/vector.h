#ifndef VECTOR_H
#define VECTOR_H

#define VECTOR_MAX_EXPAND_STEP 500

typedef enum {
	VECTOR_STATUS_OK,
	VECTOR_STATUS_ERR_ALLOC
} VECTOR_STATUS;

typedef struct {
	unsigned int size;
	unsigned int idx;
	char **data;
} vector_str;

VECTOR_STATUS vector_str_init(vector_str *vector);
VECTOR_STATUS vector_str_push(vector_str *vector, const char *src);
VECTOR_STATUS vector_str_prepend(vector_str *vector, const char *src);
VECTOR_STATUS vector_str_auto_expand(vector_str *vector);
void vector_destroy(vector_str *vector);

#endif