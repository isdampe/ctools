#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include "hashmap.h"

HASHMAP_STATUS hashmap_init(struct hashmap *map, const size_t size)
{
	map->size = size;
	map->table = malloc(map->size * sizeof(struct hashmap_entry *));
	for (size_t i=0; i<size; ++i)
		map->table[i] = NULL;

	return HASHMAP_STATUS_OK;
}

static size_t hashmap_hash_str(const struct hashmap *map, const char *key)
{
	size_t bitstack = 0x0;
	size_t i = 0;
	size_t key_length = strlen(key);

	while (bitstack < ULONG_MAX && i < key_length) {
		bitstack = (bitstack << 8) + key[i];
		i++;
	}

	return bitstack % map->size;
}

static void hashmap_auto_free(struct hashmap_entry *entry)
{
	if (entry->type == HASHMAP_DATA_TYPE_STR && entry->value.str != NULL)
		free(entry->value.str);
	free(entry->key);
	free(entry);
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

HASHMAP_STATUS hashmap_set_byte(struct hashmap *map, const char *key,
	char value)
{
	struct hashmap_entry *entry = hashmap_set_generic(map,
		HASHMAP_DATA_TYPE_BYTE, key);
	entry->value.byte = value;

	return HASHMAP_STATUS_OK;
}

HASHMAP_STATUS hashmap_set_str(struct hashmap *map, const char *key,
	char *value)
{
	struct hashmap_entry *entry = hashmap_set_generic(map,
		HASHMAP_DATA_TYPE_STR, key);

	entry->value.str = calloc(strlen(value) +1, sizeof(char));
	strcpy(entry->value.str, value);

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

char hashmap_get_byte(const struct hashmap *map, const char *key)
{
	struct hashmap_entry *ep = hashmap_get_generic(map, key);
	if (ep == NULL)
		return '\0';
	return ep->value.byte;
}

char *hashmap_get_str(const struct hashmap *map, const char *key)
{
	struct hashmap_entry *ep = hashmap_get_generic(map, key);
	if (ep == NULL)
		return "";
	return ep->value.str;
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
