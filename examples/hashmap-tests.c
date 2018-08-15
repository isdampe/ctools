#include <stdio.h>
#include "../lib/hashmap.h"

int main()
{
	struct hashmap map;
	hashmap_init(&map, 100);

	hashmap_set_str(&map, "richard", "Is really cool");
	char *str = hashmap_get_str(&map, "richard");
	printf("The string set is %s\n", str);

	hashmap_set_str(&map, "richard", "Or was really cool");
	char *nstr = hashmap_get_str(&map, "richard");
	printf("The string is now %s\n", nstr);

	//These two entries have identical hashes.
	hashmap_set_byte(&map, "da", 'b');
	hashmap_set_byte(&map, "bm", 'a');
	char byte = hashmap_get_byte(&map, "da");
	char byte2 = hashmap_get_byte(&map, "bm");
	printf("The bytes set were %c, %c\n", byte, byte2);

	hashmap_set_byte(&map, "bm", 'z');
	char byte3 = hashmap_get_byte(&map, "bm");
	printf("The final byte is %c\n", byte3);

	hashmap_destroy(&map);

	return 0;
}
