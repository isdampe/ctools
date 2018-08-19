#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hashmap.h"

HASHMAP_STATUS hashmap_init(struct hashmap *map, const size_t size)
{
	map->size = size;
	map->table = malloc(map->size * sizeof(struct hashmap_entry *));
	if (map->table == NULL)
		return HASHMAP_STATUS_ERR_ALLOC;

	for (size_t i=0; i<size; ++i)
		map->table[i] = NULL;

	return HASHMAP_STATUS_OK;
}

static size_t hashmap_hash_str(const struct hashmap *map, const char *key)
{
	size_t bitstack = 0x0;
	size_t i = 0;
	size_t key_length = strlen(key);

	while (bitstack < ULONG_MAX && i < key_length)
		bitstack = (bitstack << 8) + key[i++];

	return bitstack % map->size;
}

static void hashmap_inject_entry(struct hashmap *map, const size_t hash_key,
	const char *key, struct hashmap_entry *entry)
{
	struct hashmap_entry *ep = map->table[hash_key];
	if (ep == NULL) {
		map->table[hash_key] = entry;
		return;
	}

	if (strcmp(ep->key, key) == 0) {
		hashmap_auto_free(ep);
		map->table[hash_key] = entry;
		return;
	}

	while (ep->next != NULL) {
		if (strcmp(ep->next->key, key) == 0) {
			//Same key. Overriding. Make sure we free the thing we are overridding.
			hashmap_auto_free(ep->next);
			break;
		}
		ep = ep->next;
	}

	ep->next = entry;
}

static void hashmap_auto_free(struct hashmap_entry *entry)
{
	if (entry->type == HASHMAP_DATA_TYPE_STR && entry->value.str_u != NULL)
		free(entry->value.str_u);
	free(entry->key);
	free(entry);
}

static inline struct hashmap_entry *hashmap_set_generic(struct hashmap *map,
	const HASHMAP_DATA_TYPE type, const char *key)
{
	struct hashmap_entry *entry = malloc(sizeof(struct hashmap_entry));
	entry->type = type;
	entry->next = NULL;
	entry->key = malloc(strlen(key) +1);
	strcpy(entry->key, key);

	size_t hash_key = hashmap_hash_str(map, key);
	hashmap_inject_entry(map, hash_key, key, entry);

	return entry;
}

HASHMAP_STATUS hashmap_set_str(struct hashmap *map, const char *key,
	char *value)
{
	struct hashmap_entry *entry = hashmap_set_generic(map,
		HASHMAP_DATA_TYPE_STR, key);

	entry->value.str_u = calloc(strlen(value) +1, sizeof(char));
	if (entry->value.str_u == NULL)
		return HASHMAP_STATUS_ERR_ALLOC;

	strcpy(entry->value.str_u, value);

	return HASHMAP_STATUS_OK;
}

static inline struct hashmap_entry *hashmap_get_generic(const struct hashmap *map,
	const char *key)
{
	size_t hash_key = hashmap_hash_str(map, key);
	struct hashmap_entry *ep = map->table[hash_key];

	while (ep != NULL) {
		if (strcmp(ep->key, key) == 0)
			return ep;
		ep = ep->next;
	}

	return ep;
}

char *hashmap_get_str(const struct hashmap *map, const char *key)
{
	struct hashmap_entry *ep = hashmap_get_generic(map, key);
	if (ep == NULL)
		return "";
	return ep->value.str_u;
}

void hashmap_destroy(struct hashmap *map)
{
	for (size_t i=0; i<map->size; ++i) {
		struct hashmap_entry *entry = map->table[i];
		if (entry != NULL) {
			while (entry->next != NULL) {
				hashmap_auto_free(entry);
				entry = entry->next;
			}
			map->table[i] = NULL;
		}
	}
}

HASHMAP_STATUS hashmap_set_byte(struct hashmap *map, const char *key,
	char value)
{
	struct hashmap_entry *entry = hashmap_set_generic(map,
		HASHMAP_DATA_TYPE_BYTE, key);
	entry->value.byte_u = value;

	return HASHMAP_STATUS_OK;
}

char hashmap_get_byte(const struct hashmap *map, const char *key)
{
	struct hashmap_entry *ep = hashmap_get_generic(map, key);
	if (ep == NULL)
		return '\0';
	return ep->value.byte_u;
}


HASHMAP_STATUS hashmap_set_int(struct hashmap *map, const char *key,
	int value)
{
	struct hashmap_entry *entry = hashmap_set_generic(map,
		HASHMAP_DATA_TYPE_INT, key);
	entry->value.int_u = value;

	return HASHMAP_STATUS_OK;
}

int hashmap_get_int(const struct hashmap *map, const char *key)
{
	struct hashmap_entry *ep = hashmap_get_generic(map, key);
	if (ep == NULL)
		return '\0';
	return ep->value.int_u;
}


HASHMAP_STATUS hashmap_set_uint(struct hashmap *map, const char *key,
	unsigned int value)
{
	struct hashmap_entry *entry = hashmap_set_generic(map,
		HASHMAP_DATA_TYPE_UINT, key);
	entry->value.uint_u = value;

	return HASHMAP_STATUS_OK;
}

unsigned int hashmap_get_uint(const struct hashmap *map, const char *key)
{
	struct hashmap_entry *ep = hashmap_get_generic(map, key);
	if (ep == NULL)
		return '\0';
	return ep->value.uint_u;
}


HASHMAP_STATUS hashmap_set_long(struct hashmap *map, const char *key,
	long value)
{
	struct hashmap_entry *entry = hashmap_set_generic(map,
		HASHMAP_DATA_TYPE_LONG, key);
	entry->value.long_u = value;

	return HASHMAP_STATUS_OK;
}

long hashmap_get_long(const struct hashmap *map, const char *key)
{
	struct hashmap_entry *ep = hashmap_get_generic(map, key);
	if (ep == NULL)
		return '\0';
	return ep->value.long_u;
}


HASHMAP_STATUS hashmap_set_ulong(struct hashmap *map, const char *key,
	unsigned long value)
{
	struct hashmap_entry *entry = hashmap_set_generic(map,
		HASHMAP_DATA_TYPE_ULONG, key);
	entry->value.ulong_u = value;

	return HASHMAP_STATUS_OK;
}

unsigned long hashmap_get_ulong(const struct hashmap *map, const char *key)
{
	struct hashmap_entry *ep = hashmap_get_generic(map, key);
	if (ep == NULL)
		return '\0';
	return ep->value.ulong_u;
}


HASHMAP_STATUS hashmap_set_float(struct hashmap *map, const char *key,
	float value)
{
	struct hashmap_entry *entry = hashmap_set_generic(map,
		HASHMAP_DATA_TYPE_FLOAT, key);
	entry->value.float_u = value;

	return HASHMAP_STATUS_OK;
}

float hashmap_get_float(const struct hashmap *map, const char *key)
{
	struct hashmap_entry *ep = hashmap_get_generic(map, key);
	if (ep == NULL)
		return '\0';
	return ep->value.float_u;
}


HASHMAP_STATUS hashmap_set_double(struct hashmap *map, const char *key,
	double value)
{
	struct hashmap_entry *entry = hashmap_set_generic(map,
		HASHMAP_DATA_TYPE_DOUBLE, key);
	entry->value.double_u = value;

	return HASHMAP_STATUS_OK;
}

double hashmap_get_double(const struct hashmap *map, const char *key)
{
	struct hashmap_entry *ep = hashmap_get_generic(map, key);
	if (ep == NULL)
		return '\0';
	return ep->value.double_u;
}


HASHMAP_STATUS hashmap_set_bool(struct hashmap *map, const char *key,
	bool value)
{
	struct hashmap_entry *entry = hashmap_set_generic(map,
		HASHMAP_DATA_TYPE_BOOL, key);
	entry->value.bool_u = value;

	return HASHMAP_STATUS_OK;
}

bool hashmap_get_bool(const struct hashmap *map, const char *key)
{
	struct hashmap_entry *ep = hashmap_get_generic(map, key);
	if (ep == NULL)
		return '\0';
	return ep->value.bool_u;
}


