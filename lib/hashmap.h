#ifndef HASHMAP_H
#define HASHMAP_H
#include <stddef.h>

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
	HASHMAP_DATA_TYPE_STR,
} HASHMAP_DATA_TYPE;

struct hashmap_entry {
	char *key;
	HASHMAP_DATA_TYPE type;
	union {
		char byte;
		int i;
		unsigned int ui;
		long l;
		unsigned long ul;
		float f;
		double d;
		char *str;
	} value;
	struct hashmap_entry *next;
};

struct hashmap {
	size_t size;
	struct hashmap_entry **table;
};

HASHMAP_STATUS hashmap_init(struct hashmap *map, const size_t size);
static size_t hashmap_hash_str(const struct hashmap *map, const char *key);
static inline struct hashmap_entry *hashmap_set_generic(struct hashmap *map,
	const HASHMAP_DATA_TYPE type, const char *key);
HASHMAP_STATUS hashmap_set_byte(struct hashmap *map, const char *key,
	char value);
HASHMAP_STATUS hashmap_set_str(struct hashmap *map, const char *key,
	char *value);
static inline struct hashmap_entry *hashmap_get_generic(const struct hashmap *map,
	const char *key);
static void hashmap_auto_free(struct hashmap_entry *entry);
char hashmap_get_byte(const struct hashmap *map, const char *key);
char *hashmap_get_str(const struct hashmap *map, const char *key);
void hashmap_destroy(struct hashmap *map);

#endif
