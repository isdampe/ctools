#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include "vector.h"

VECTOR_STATUS vector_init_str(struct vector_str *vector)
{
	vector->size = 100;
	vector->idx = 0;
	vector->data = calloc(vector->size, sizeof(char *));

	return (!vector->data ? VECTOR_STATUS_ERR_ALLOC : VECTOR_STATUS_OK);
}

VECTOR_STATUS vector_push_str(struct vector_str *vector, const char *src)
{
	vector->data[vector->idx++] = calloc(strlen(src) +1, sizeof(char));
	strcpy(vector->data[vector->idx -1], src);

	if (vector->idx == vector->size) {
		VECTOR_STATUS result = vector_auto_expand_str(vector);
		if (result != VECTOR_STATUS_OK)
			return result;
	}

	return (!vector->data[vector->idx -1] ?
		VECTOR_STATUS_ERR_ALLOC : VECTOR_STATUS_OK);
}

VECTOR_STATUS vector_prepend_str(struct vector_str *vector, const char *src)
{
	VECTOR_STATUS result = vector_push_str(vector, src);
	char *tmp = vector->data[0];
	vector->data[0] = vector->data[vector->idx];
	vector->data[vector->idx] = tmp;

	return result;
}

static VECTOR_STATUS vector_auto_expand_str(struct vector_str *vector)
{
	vector->size += VECTOR_MAX_EXPAND_STEP;
	vector->data = realloc(vector->data, vector->size * sizeof(char *));

	return (!vector->data ? VECTOR_STATUS_ERR_ALLOC : VECTOR_STATUS_OK);
}

long vector_search_str(struct vector_str *vector, const char *src)
{
	for (long i=0; i<vector->idx; ++i)
		if (strcmp(vector->data[i], src) == 0)
			return i;

	return -1;
}

VECTOR_STATUS vector_pop_str(struct vector_str *vector)
{
	if (vector->idx == 0)
		return VECTOR_STATUS_ERR_UNDERFLOW;

	free(vector->data[--vector->idx]);
	if (vector->size - vector->idx > (2 * VECTOR_MAX_EXPAND_STEP)) {
		VECTOR_STATUS result = vector_auto_shrink_str(vector);
		if (result != VECTOR_STATUS_OK)
			return result;
	}

	return VECTOR_STATUS_OK;
}

static VECTOR_STATUS vector_auto_shrink_str(struct vector_str *vector)
{
	vector->size -= VECTOR_MAX_EXPAND_STEP;
	vector->data = realloc(vector->data, vector->size * sizeof(char *));

	return (!vector->data ? VECTOR_STATUS_ERR_ALLOC : VECTOR_STATUS_OK);
}

void vector_destroy_str(struct vector_str *vector) {
	for (long i=0; i<vector->idx; ++i)
		free(vector->data[i]);
	free(vector->data);
}

//<DYNAMIC_ENTRIES>
