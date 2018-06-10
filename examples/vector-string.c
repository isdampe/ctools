#include <stdio.h>
#include "../lib/vector.h"

int main(int argc, char **argv) {
	vector_str vector;
	vector_init_str(&vector);

	printf("Allocating...\n");
	for (int i=0; i<150000000; ++i) {
		//printf("Size: %i, index: %i\n", vector.size, vector.idx);
		if (vector_push_str(&vector, "Hello world.") == VECTOR_STATUS_ERR_ALLOC) {
			printf("Error allocating at %i\n", i);
			return 1;
		}
	}

	printf("Freeing...\n");
	for (int i=150000000; i>0; --i) {
		if (vector_pop(&vector) != VECTOR_STATUS_OK) {
			printf("AN ERROR OCCURED!\n");
			return 1;
		}
	}

	vector_destroy_str(&vector);

	vector_init_str(&vector);
	vector_push_str(&vector, "A");
	vector_push_str(&vector, "quick");
	vector_push_str(&vector, "brown");
	vector_push_str(&vector, "fox");
	vector_push_str(&vector, "jumps");

	long idx = vector_search_str(&vector, "brown");
	if (idx < 0)
		printf("String not found in vector.\n");
	else {
		printf("String found at index %li\n", idx);
		printf("The string is: %s\n", vector.data[idx]);
	}

	vector_destroy_str(&vector);

	return 0;
}