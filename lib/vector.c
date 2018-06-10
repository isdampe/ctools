#include <stdlib.h>
#include <string.h>
#include "vector.h"

VECTOR_STATUS vector_str_init(vector_str *vector) {
	vector->size = 100;
	vector->idx = 0;
	vector->data = calloc(vector->size, sizeof(char *));

	return (!vector->data ? VECTOR_STATUS_ERR_ALLOC : VECTOR_STATUS_OK);
}

VECTOR_STATUS vector_str_push(vector_str *vector, const char *src) {
	vector->data[vector->idx++] = calloc(strlen(src) +1, sizeof(char));
	strcpy(vector->data[vector->idx -1], src);

	if (vector->idx == vector->size) {
		VECTOR_STATUS result = vector_str_auto_expand(vector);
		if (result != VECTOR_STATUS_OK)
			return result;
	}
	
	return (!vector->data[vector->idx -1] ? VECTOR_STATUS_ERR_ALLOC : VECTOR_STATUS_OK);
}

VECTOR_STATUS vector_str_prepend(vector_str *vector, const char *src) {
	VECTOR_STATUS result = vector_str_push(vector, src);
	char *tmp = vector->data[0];
	vector->data[0] = vector->data[vector->idx];
	vector->data[vector->idx] = tmp;

	return result;
}

VECTOR_STATUS vector_str_auto_expand(vector_str *vector) {
	vector->size += VECTOR_MAX_EXPAND_STEP;
	vector->data = realloc(vector->data, vector->size * sizeof(char *));

	return (!vector->data ? VECTOR_STATUS_ERR_ALLOC : VECTOR_STATUS_OK);
}

void vector_destroy(vector_str *vector) {
	for (unsigned int i=0; i<vector->idx; ++i)
		free(vector->data[i]);
	free(vector->data);
}