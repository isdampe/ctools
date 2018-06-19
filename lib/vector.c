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

VECTOR_STATUS vector_init_int(struct vector_int *vector)
{
	vector->size = 100;
	vector->idx = 0;
	vector->data = calloc(vector->size, sizeof(int));

	return (!vector->data ? VECTOR_STATUS_ERR_ALLOC : VECTOR_STATUS_OK);
}

VECTOR_STATUS vector_push_int(struct vector_int *vector,
	const int src)
{
	vector->data[vector->idx++] = src;

	if (vector->idx == vector->size) {
		VECTOR_STATUS result = vector_auto_expand_int(vector);
		if (result != VECTOR_STATUS_OK)
			return result;
	}

	return VECTOR_STATUS_OK;
}

VECTOR_STATUS vector_prepend_int(struct vector_int *vector,
	const int src)
{
	VECTOR_STATUS result = vector_push_int(vector, src);
	int tmp = vector->data[0];
	vector->data[0] = vector->data[vector->idx];
	vector->data[vector->idx] = tmp;

	return result;
}

static VECTOR_STATUS vector_auto_expand_int(struct vector_int *vector)
{
	vector->size += VECTOR_MAX_EXPAND_STEP;
	vector->data = realloc(vector->data, vector->size * sizeof(int));

	return (!vector->data ? VECTOR_STATUS_ERR_ALLOC : VECTOR_STATUS_OK);
}

long vector_search_int(struct vector_int *vector, const int src)
{
	for (long i=0; i<vector->idx; ++i)
		if (vector->data[i] == src)
			return i;

	return -1;
}

VECTOR_STATUS vector_pop_int(struct vector_int *vector)
{
	if (vector->idx == 0)
		return VECTOR_STATUS_ERR_UNDERFLOW;

	vector->data[--vector->idx] = 0;
	if (vector->size - vector->idx > (2 * VECTOR_MAX_EXPAND_STEP)) {
		VECTOR_STATUS result = vector_auto_shrink_int(vector);
		if (result != VECTOR_STATUS_OK)
			return result;
	}

	return VECTOR_STATUS_OK;
}

static VECTOR_STATUS vector_auto_shrink_int(struct vector_int *vector)
{
	vector->size -= VECTOR_MAX_EXPAND_STEP;
	vector->data = realloc(vector->data, vector->size * sizeof(int));

	return (!vector->data ? VECTOR_STATUS_ERR_ALLOC : VECTOR_STATUS_OK);
}

void vector_destroy_int(struct vector_int *vector) {
	free(vector->data);
}


VECTOR_STATUS vector_init_uint(struct vector_uint *vector)
{
	vector->size = 100;
	vector->idx = 0;
	vector->data = calloc(vector->size, sizeof(unsigned int));

	return (!vector->data ? VECTOR_STATUS_ERR_ALLOC : VECTOR_STATUS_OK);
}

VECTOR_STATUS vector_push_uint(struct vector_uint *vector,
	const unsigned int src)
{
	vector->data[vector->idx++] = src;

	if (vector->idx == vector->size) {
		VECTOR_STATUS result = vector_auto_expand_uint(vector);
		if (result != VECTOR_STATUS_OK)
			return result;
	}

	return VECTOR_STATUS_OK;
}

VECTOR_STATUS vector_prepend_uint(struct vector_uint *vector,
	const unsigned int src)
{
	VECTOR_STATUS result = vector_push_uint(vector, src);
	unsigned int tmp = vector->data[0];
	vector->data[0] = vector->data[vector->idx];
	vector->data[vector->idx] = tmp;

	return result;
}

static VECTOR_STATUS vector_auto_expand_uint(struct vector_uint *vector)
{
	vector->size += VECTOR_MAX_EXPAND_STEP;
	vector->data = realloc(vector->data, vector->size * sizeof(unsigned int));

	return (!vector->data ? VECTOR_STATUS_ERR_ALLOC : VECTOR_STATUS_OK);
}

long vector_search_uint(struct vector_uint *vector, const unsigned int src)
{
	for (long i=0; i<vector->idx; ++i)
		if (vector->data[i] == src)
			return i;

	return -1;
}

VECTOR_STATUS vector_pop_uint(struct vector_uint *vector)
{
	if (vector->idx == 0)
		return VECTOR_STATUS_ERR_UNDERFLOW;

	vector->data[--vector->idx] = 0;
	if (vector->size - vector->idx > (2 * VECTOR_MAX_EXPAND_STEP)) {
		VECTOR_STATUS result = vector_auto_shrink_uint(vector);
		if (result != VECTOR_STATUS_OK)
			return result;
	}

	return VECTOR_STATUS_OK;
}

static VECTOR_STATUS vector_auto_shrink_uint(struct vector_uint *vector)
{
	vector->size -= VECTOR_MAX_EXPAND_STEP;
	vector->data = realloc(vector->data, vector->size * sizeof(unsigned int));

	return (!vector->data ? VECTOR_STATUS_ERR_ALLOC : VECTOR_STATUS_OK);
}

void vector_destroy_uint(struct vector_uint *vector) {
	free(vector->data);
}


VECTOR_STATUS vector_init_long(struct vector_long *vector)
{
	vector->size = 100;
	vector->idx = 0;
	vector->data = calloc(vector->size, sizeof(long));

	return (!vector->data ? VECTOR_STATUS_ERR_ALLOC : VECTOR_STATUS_OK);
}

VECTOR_STATUS vector_push_long(struct vector_long *vector,
	const long src)
{
	vector->data[vector->idx++] = src;

	if (vector->idx == vector->size) {
		VECTOR_STATUS result = vector_auto_expand_long(vector);
		if (result != VECTOR_STATUS_OK)
			return result;
	}

	return VECTOR_STATUS_OK;
}

VECTOR_STATUS vector_prepend_long(struct vector_long *vector,
	const long src)
{
	VECTOR_STATUS result = vector_push_long(vector, src);
	long tmp = vector->data[0];
	vector->data[0] = vector->data[vector->idx];
	vector->data[vector->idx] = tmp;

	return result;
}

static VECTOR_STATUS vector_auto_expand_long(struct vector_long *vector)
{
	vector->size += VECTOR_MAX_EXPAND_STEP;
	vector->data = realloc(vector->data, vector->size * sizeof(long));

	return (!vector->data ? VECTOR_STATUS_ERR_ALLOC : VECTOR_STATUS_OK);
}

long vector_search_long(struct vector_long *vector, const long src)
{
	for (long i=0; i<vector->idx; ++i)
		if (vector->data[i] == src)
			return i;

	return -1;
}

VECTOR_STATUS vector_pop_long(struct vector_long *vector)
{
	if (vector->idx == 0)
		return VECTOR_STATUS_ERR_UNDERFLOW;

	vector->data[--vector->idx] = 0;
	if (vector->size - vector->idx > (2 * VECTOR_MAX_EXPAND_STEP)) {
		VECTOR_STATUS result = vector_auto_shrink_long(vector);
		if (result != VECTOR_STATUS_OK)
			return result;
	}

	return VECTOR_STATUS_OK;
}

static VECTOR_STATUS vector_auto_shrink_long(struct vector_long *vector)
{
	vector->size -= VECTOR_MAX_EXPAND_STEP;
	vector->data = realloc(vector->data, vector->size * sizeof(long));

	return (!vector->data ? VECTOR_STATUS_ERR_ALLOC : VECTOR_STATUS_OK);
}

void vector_destroy_long(struct vector_long *vector) {
	free(vector->data);
}


VECTOR_STATUS vector_init_ulong(struct vector_ulong *vector)
{
	vector->size = 100;
	vector->idx = 0;
	vector->data = calloc(vector->size, sizeof(unsigned long));

	return (!vector->data ? VECTOR_STATUS_ERR_ALLOC : VECTOR_STATUS_OK);
}

VECTOR_STATUS vector_push_ulong(struct vector_ulong *vector,
	const unsigned long src)
{
	vector->data[vector->idx++] = src;

	if (vector->idx == vector->size) {
		VECTOR_STATUS result = vector_auto_expand_ulong(vector);
		if (result != VECTOR_STATUS_OK)
			return result;
	}

	return VECTOR_STATUS_OK;
}

VECTOR_STATUS vector_prepend_ulong(struct vector_ulong *vector,
	const unsigned long src)
{
	VECTOR_STATUS result = vector_push_ulong(vector, src);
	unsigned long tmp = vector->data[0];
	vector->data[0] = vector->data[vector->idx];
	vector->data[vector->idx] = tmp;

	return result;
}

static VECTOR_STATUS vector_auto_expand_ulong(struct vector_ulong *vector)
{
	vector->size += VECTOR_MAX_EXPAND_STEP;
	vector->data = realloc(vector->data, vector->size * sizeof(unsigned long));

	return (!vector->data ? VECTOR_STATUS_ERR_ALLOC : VECTOR_STATUS_OK);
}

long vector_search_ulong(struct vector_ulong *vector, const unsigned long src)
{
	for (long i=0; i<vector->idx; ++i)
		if (vector->data[i] == src)
			return i;

	return -1;
}

VECTOR_STATUS vector_pop_ulong(struct vector_ulong *vector)
{
	if (vector->idx == 0)
		return VECTOR_STATUS_ERR_UNDERFLOW;

	vector->data[--vector->idx] = 0;
	if (vector->size - vector->idx > (2 * VECTOR_MAX_EXPAND_STEP)) {
		VECTOR_STATUS result = vector_auto_shrink_ulong(vector);
		if (result != VECTOR_STATUS_OK)
			return result;
	}

	return VECTOR_STATUS_OK;
}

static VECTOR_STATUS vector_auto_shrink_ulong(struct vector_ulong *vector)
{
	vector->size -= VECTOR_MAX_EXPAND_STEP;
	vector->data = realloc(vector->data, vector->size * sizeof(unsigned long));

	return (!vector->data ? VECTOR_STATUS_ERR_ALLOC : VECTOR_STATUS_OK);
}

void vector_destroy_ulong(struct vector_ulong *vector) {
	free(vector->data);
}


VECTOR_STATUS vector_init_float(struct vector_float *vector)
{
	vector->size = 100;
	vector->idx = 0;
	vector->data = calloc(vector->size, sizeof(float));

	return (!vector->data ? VECTOR_STATUS_ERR_ALLOC : VECTOR_STATUS_OK);
}

VECTOR_STATUS vector_push_float(struct vector_float *vector,
	const float src)
{
	vector->data[vector->idx++] = src;

	if (vector->idx == vector->size) {
		VECTOR_STATUS result = vector_auto_expand_float(vector);
		if (result != VECTOR_STATUS_OK)
			return result;
	}

	return VECTOR_STATUS_OK;
}

VECTOR_STATUS vector_prepend_float(struct vector_float *vector,
	const float src)
{
	VECTOR_STATUS result = vector_push_float(vector, src);
	float tmp = vector->data[0];
	vector->data[0] = vector->data[vector->idx];
	vector->data[vector->idx] = tmp;

	return result;
}

static VECTOR_STATUS vector_auto_expand_float(struct vector_float *vector)
{
	vector->size += VECTOR_MAX_EXPAND_STEP;
	vector->data = realloc(vector->data, vector->size * sizeof(float));

	return (!vector->data ? VECTOR_STATUS_ERR_ALLOC : VECTOR_STATUS_OK);
}

long vector_search_float(struct vector_float *vector, const float src)
{
	for (long i=0; i<vector->idx; ++i)
		if (vector->data[i] == src)
			return i;

	return -1;
}

VECTOR_STATUS vector_pop_float(struct vector_float *vector)
{
	if (vector->idx == 0)
		return VECTOR_STATUS_ERR_UNDERFLOW;

	vector->data[--vector->idx] = 0;
	if (vector->size - vector->idx > (2 * VECTOR_MAX_EXPAND_STEP)) {
		VECTOR_STATUS result = vector_auto_shrink_float(vector);
		if (result != VECTOR_STATUS_OK)
			return result;
	}

	return VECTOR_STATUS_OK;
}

static VECTOR_STATUS vector_auto_shrink_float(struct vector_float *vector)
{
	vector->size -= VECTOR_MAX_EXPAND_STEP;
	vector->data = realloc(vector->data, vector->size * sizeof(float));

	return (!vector->data ? VECTOR_STATUS_ERR_ALLOC : VECTOR_STATUS_OK);
}

void vector_destroy_float(struct vector_float *vector) {
	free(vector->data);
}


VECTOR_STATUS vector_init_double(struct vector_double *vector)
{
	vector->size = 100;
	vector->idx = 0;
	vector->data = calloc(vector->size, sizeof(double));

	return (!vector->data ? VECTOR_STATUS_ERR_ALLOC : VECTOR_STATUS_OK);
}

VECTOR_STATUS vector_push_double(struct vector_double *vector,
	const double src)
{
	vector->data[vector->idx++] = src;

	if (vector->idx == vector->size) {
		VECTOR_STATUS result = vector_auto_expand_double(vector);
		if (result != VECTOR_STATUS_OK)
			return result;
	}

	return VECTOR_STATUS_OK;
}

VECTOR_STATUS vector_prepend_double(struct vector_double *vector,
	const double src)
{
	VECTOR_STATUS result = vector_push_double(vector, src);
	double tmp = vector->data[0];
	vector->data[0] = vector->data[vector->idx];
	vector->data[vector->idx] = tmp;

	return result;
}

static VECTOR_STATUS vector_auto_expand_double(struct vector_double *vector)
{
	vector->size += VECTOR_MAX_EXPAND_STEP;
	vector->data = realloc(vector->data, vector->size * sizeof(double));

	return (!vector->data ? VECTOR_STATUS_ERR_ALLOC : VECTOR_STATUS_OK);
}

long vector_search_double(struct vector_double *vector, const double src)
{
	for (long i=0; i<vector->idx; ++i)
		if (vector->data[i] == src)
			return i;

	return -1;
}

VECTOR_STATUS vector_pop_double(struct vector_double *vector)
{
	if (vector->idx == 0)
		return VECTOR_STATUS_ERR_UNDERFLOW;

	vector->data[--vector->idx] = 0;
	if (vector->size - vector->idx > (2 * VECTOR_MAX_EXPAND_STEP)) {
		VECTOR_STATUS result = vector_auto_shrink_double(vector);
		if (result != VECTOR_STATUS_OK)
			return result;
	}

	return VECTOR_STATUS_OK;
}

static VECTOR_STATUS vector_auto_shrink_double(struct vector_double *vector)
{
	vector->size -= VECTOR_MAX_EXPAND_STEP;
	vector->data = realloc(vector->data, vector->size * sizeof(double));

	return (!vector->data ? VECTOR_STATUS_ERR_ALLOC : VECTOR_STATUS_OK);
}

void vector_destroy_double(struct vector_double *vector) {
	free(vector->data);
}


VECTOR_STATUS vector_init_bool(struct vector_bool *vector)
{
	vector->size = 100;
	vector->idx = 0;
	vector->data = calloc(vector->size, sizeof(bool));

	return (!vector->data ? VECTOR_STATUS_ERR_ALLOC : VECTOR_STATUS_OK);
}

VECTOR_STATUS vector_push_bool(struct vector_bool *vector,
	const bool src)
{
	vector->data[vector->idx++] = src;

	if (vector->idx == vector->size) {
		VECTOR_STATUS result = vector_auto_expand_bool(vector);
		if (result != VECTOR_STATUS_OK)
			return result;
	}

	return VECTOR_STATUS_OK;
}

VECTOR_STATUS vector_prepend_bool(struct vector_bool *vector,
	const bool src)
{
	VECTOR_STATUS result = vector_push_bool(vector, src);
	bool tmp = vector->data[0];
	vector->data[0] = vector->data[vector->idx];
	vector->data[vector->idx] = tmp;

	return result;
}

static VECTOR_STATUS vector_auto_expand_bool(struct vector_bool *vector)
{
	vector->size += VECTOR_MAX_EXPAND_STEP;
	vector->data = realloc(vector->data, vector->size * sizeof(bool));

	return (!vector->data ? VECTOR_STATUS_ERR_ALLOC : VECTOR_STATUS_OK);
}

long vector_search_bool(struct vector_bool *vector, const bool src)
{
	for (long i=0; i<vector->idx; ++i)
		if (vector->data[i] == src)
			return i;

	return -1;
}

VECTOR_STATUS vector_pop_bool(struct vector_bool *vector)
{
	if (vector->idx == 0)
		return VECTOR_STATUS_ERR_UNDERFLOW;

	vector->data[--vector->idx] = 0;
	if (vector->size - vector->idx > (2 * VECTOR_MAX_EXPAND_STEP)) {
		VECTOR_STATUS result = vector_auto_shrink_bool(vector);
		if (result != VECTOR_STATUS_OK)
			return result;
	}

	return VECTOR_STATUS_OK;
}

static VECTOR_STATUS vector_auto_shrink_bool(struct vector_bool *vector)
{
	vector->size -= VECTOR_MAX_EXPAND_STEP;
	vector->data = realloc(vector->data, vector->size * sizeof(bool));

	return (!vector->data ? VECTOR_STATUS_ERR_ALLOC : VECTOR_STATUS_OK);
}

void vector_destroy_bool(struct vector_bool *vector) {
	free(vector->data);
}


