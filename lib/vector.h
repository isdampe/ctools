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
static VECTOR_STATUS vector_auto_shrink_str(struct vector_str *vector);
void vector_destroy_str(struct vector_str *vector);

struct vector_int {
	long size;
	long idx;
	int *data;
};

VECTOR_STATUS vector_init_int(struct vector_int *vector);
VECTOR_STATUS vector_push_int(struct vector_int *vector, const int src);
VECTOR_STATUS vector_prepend_int(struct vector_int *vector, const int src);
static VECTOR_STATUS vector_auto_expand_int(struct vector_int *vector);
long vector_search_int(struct vector_int *vector, const int src);
VECTOR_STATUS vector_pop_int(struct vector_int *vector);
static VECTOR_STATUS vector_auto_shrink_int(struct vector_int *vector);
void vector_destroy_int(struct vector_int *vector);


struct vector_uint {
	long size;
	long idx;
	unsigned int *data;
};

VECTOR_STATUS vector_init_uint(struct vector_uint *vector);
VECTOR_STATUS vector_push_uint(struct vector_uint *vector, const unsigned int src);
VECTOR_STATUS vector_prepend_uint(struct vector_uint *vector, const unsigned int src);
static VECTOR_STATUS vector_auto_expand_uint(struct vector_uint *vector);
long vector_search_uint(struct vector_uint *vector, const unsigned int src);
VECTOR_STATUS vector_pop_uint(struct vector_uint *vector);
static VECTOR_STATUS vector_auto_shrink_uint(struct vector_uint *vector);
void vector_destroy_uint(struct vector_uint *vector);


struct vector_long {
	long size;
	long idx;
	long *data;
};

VECTOR_STATUS vector_init_long(struct vector_long *vector);
VECTOR_STATUS vector_push_long(struct vector_long *vector, const long src);
VECTOR_STATUS vector_prepend_long(struct vector_long *vector, const long src);
static VECTOR_STATUS vector_auto_expand_long(struct vector_long *vector);
long vector_search_long(struct vector_long *vector, const long src);
VECTOR_STATUS vector_pop_long(struct vector_long *vector);
static VECTOR_STATUS vector_auto_shrink_long(struct vector_long *vector);
void vector_destroy_long(struct vector_long *vector);


struct vector_ulong {
	long size;
	long idx;
	unsigned long *data;
};

VECTOR_STATUS vector_init_ulong(struct vector_ulong *vector);
VECTOR_STATUS vector_push_ulong(struct vector_ulong *vector, const unsigned long src);
VECTOR_STATUS vector_prepend_ulong(struct vector_ulong *vector, const unsigned long src);
static VECTOR_STATUS vector_auto_expand_ulong(struct vector_ulong *vector);
long vector_search_ulong(struct vector_ulong *vector, const unsigned long src);
VECTOR_STATUS vector_pop_ulong(struct vector_ulong *vector);
static VECTOR_STATUS vector_auto_shrink_ulong(struct vector_ulong *vector);
void vector_destroy_ulong(struct vector_ulong *vector);


struct vector_float {
	long size;
	long idx;
	float *data;
};

VECTOR_STATUS vector_init_float(struct vector_float *vector);
VECTOR_STATUS vector_push_float(struct vector_float *vector, const float src);
VECTOR_STATUS vector_prepend_float(struct vector_float *vector, const float src);
static VECTOR_STATUS vector_auto_expand_float(struct vector_float *vector);
long vector_search_float(struct vector_float *vector, const float src);
VECTOR_STATUS vector_pop_float(struct vector_float *vector);
static VECTOR_STATUS vector_auto_shrink_float(struct vector_float *vector);
void vector_destroy_float(struct vector_float *vector);


struct vector_double {
	long size;
	long idx;
	double *data;
};

VECTOR_STATUS vector_init_double(struct vector_double *vector);
VECTOR_STATUS vector_push_double(struct vector_double *vector, const double src);
VECTOR_STATUS vector_prepend_double(struct vector_double *vector, const double src);
static VECTOR_STATUS vector_auto_expand_double(struct vector_double *vector);
long vector_search_double(struct vector_double *vector, const double src);
VECTOR_STATUS vector_pop_double(struct vector_double *vector);
static VECTOR_STATUS vector_auto_shrink_double(struct vector_double *vector);
void vector_destroy_double(struct vector_double *vector);


struct vector_bool {
	long size;
	long idx;
	bool *data;
};

VECTOR_STATUS vector_init_bool(struct vector_bool *vector);
VECTOR_STATUS vector_push_bool(struct vector_bool *vector, const bool src);
VECTOR_STATUS vector_prepend_bool(struct vector_bool *vector, const bool src);
static VECTOR_STATUS vector_auto_expand_bool(struct vector_bool *vector);
long vector_search_bool(struct vector_bool *vector, const bool src);
VECTOR_STATUS vector_pop_bool(struct vector_bool *vector);
static VECTOR_STATUS vector_auto_shrink_bool(struct vector_bool *vector);
void vector_destroy_bool(struct vector_bool *vector);


#endif

