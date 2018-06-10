#include <stdio.h>
#include "../lib/vector.h"

int main(int argc, char **argv) {
	vector_str vector;
	vector_str_init(&vector);

	for (int i=0; i<1500000000; ++i) {
		//printf("Size: %i, index: %i\n", vector.size, vector.idx);
		if (vector_str_push(&vector, "Hello world.") == VECTOR_STATUS_ERR_ALLOC) {
			printf("Error allocating at %i\n", i);
			return 1;
		}
	}

	for (int i=0; i<1500; ++i) {
		printf("The string is %s.\n", vector.data[i]);
	}

	vector_destroy(&vector);

	return 0;
}