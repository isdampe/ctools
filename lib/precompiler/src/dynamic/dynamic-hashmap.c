HASHMAP_STATUS hashmap_set_<TYPE>(struct hashmap *map, const char *key,
	<INPUT_TYPE> value)
{
	struct hashmap_entry *entry = hashmap_set_generic(map,
		HASHMAP_DATA_TYPE_<UPPER_TYPE>, key);
	entry->value.<TYPE>_u = value;

	return HASHMAP_STATUS_OK;
}

<INPUT_TYPE> hashmap_get_<TYPE>(const struct hashmap *map, const char *key)
{
	struct hashmap_entry *ep = hashmap_get_generic(map, key);
	if (ep == NULL)
		return '\0';
	return ep->value.<TYPE>_u;
}
