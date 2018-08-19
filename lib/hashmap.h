#ifndef HASHMAP_H
#define HASHMAP_H
#include <stddef.h>
#include <stdbool.h>

typedef enum {
	HASHMAP_STATUS_OK,
	HASHMAP_STATUS_ERR_ALLOC,
	HASHMAP_STATUS_ERR_UNDERFLOW
} HASHMAP_STATUS;

typedef enum {
	HASHMAP_DATA_TYPE_BYTE,
	HASHMAP_DATA_TYPE_INT,
	HASHMAP_DATA_TYPE_UINT,
	HASHMAP_DATA_TYPE_LONG,
	HASHMAP_DATA_TYPE_ULONG,
	HASHMAP_DATA_TYPE_FLOAT,
	HASHMAP_DATA_TYPE_DOUBLE,
	HASHMAP_DATA_TYPE_BOOL,
	HASHMAP_DATA_TYPE_STR,
} HASHMAP_DATA_TYPE;

struct hashmap_entry {
	char *key;
	HASHMAP_DATA_TYPE type;
	union {
		char byte_u;
		bool bool_u;
		int int_u;
		unsigned int uint_u;
		long long_u;
		unsigned long ulong_u;
		float float_u;
		double double_u;
		char *str_u;
	} value;
	struct hashmap_entry *next;
};

struct hashmap {
	size_t size;
	struct hashmap_entry **table;
};

HASHMAP_STATUS hashmap_init(struct hashmap *map, const size_t size);
static size_t hashmap_hash_str(const struct hashmap *map, const char *key);
static void hashmap_inject_entry(struct hashmap *map, const size_t hash_key,
	const char *key, struct hashmap_entry *entry);
static void hashmap_auto_free(struct hashmap_entry *entry);
static inline struct hashmap_entry *hashmap_set_generic(struct hashmap *map,
	const HASHMAP_DATA_TYPE type, const char *key);
HASHMAP_STATUS hashmap_set_byte(struct hashmap *map, const char *key,
	char value);
HASHMAP_STATUS hashmap_set_str(struct hashmap *map, const char *key,
	char *value);
static inline struct hashmap_entry *hashmap_get_generic(const struct hashmap *map,
	const char *key);
char hashmap_get_byte(const struct hashmap *map, const char *key);
char *hashmap_get_str(const struct hashmap *map, const char *key);
void hashmap_destroy(struct hashmap *map);

HASHMAP_STATUS hashmap_set_byte(struct hashmap *map, const char *key,
	char value);
char hashmap_get_byte(const struct hashmap *map, const char *key);


HASHMAP_STATUS hashmap_set_int(struct hashmap *map, const char *key,
	int value);
int hashmap_get_int(const struct hashmap *map, const char *key);


HASHMAP_STATUS hashmap_set_uint(struct hashmap *map, const char *key,
	unsigned int value);
unsigned int hashmap_get_uint(const struct hashmap *map, const char *key);


HASHMAP_STATUS hashmap_set_long(struct hashmap *map, const char *key,
	long value);
long hashmap_get_long(const struct hashmap *map, const char *key);


HASHMAP_STATUS hashmap_set_ulong(struct hashmap *map, const char *key,
	unsigned long value);
unsigned long hashmap_get_ulong(const struct hashmap *map, const char *key);


HASHMAP_STATUS hashmap_set_float(struct hashmap *map, const char *key,
	float value);
float hashmap_get_float(const struct hashmap *map, const char *key);


HASHMAP_STATUS hashmap_set_double(struct hashmap *map, const char *key,
	double value);
double hashmap_get_double(const struct hashmap *map, const char *key);


HASHMAP_STATUS hashmap_set_bool(struct hashmap *map, const char *key,
	bool value);
bool hashmap_get_bool(const struct hashmap *map, const char *key);


#endif

