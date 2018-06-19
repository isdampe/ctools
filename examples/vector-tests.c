#include <stdio.h>
#include "../lib/vector.h"

int main(int argc, char **argv)
{
	const int MAX_ALLOCATE_PER_TEST = 15000;
	struct vector_str string_vector;
	struct vector_int int_vector;
	struct vector_uint uint_vector;
	struct vector_long long_vector;
	struct vector_ulong ulong_vector;
	struct vector_float float_vector;
	struct vector_double double_vector;
	struct vector_bool bool_vector;

	/**
	 * Vector string tests.
	 * Allocate MAX_ALLOCATE_PER_TEST dynamic strings.
	 * Pop MAX_ALLOCATE_PER_TEST dynamic strings.
	 * Destroy string vector.
	 */
	vector_init_str(&string_vector);
	printf("Allocating %i vector_str slots...\n", MAX_ALLOCATE_PER_TEST);
	for (int i=0; i<MAX_ALLOCATE_PER_TEST; ++i) {
		if (vector_push_str(&string_vector, "Hello world.") !=
			VECTOR_STATUS_OK) {
			printf("Error allocating a string into vector_str at index %i\n",
				i);
			return 1;
		}
	}

	printf("vector_str:\tsize: %li\tidx: %li\n", string_vector.size,
		string_vector.idx);

	printf("Popping %i vector_str slots...\n", MAX_ALLOCATE_PER_TEST);
	for (int i=0; i<MAX_ALLOCATE_PER_TEST; ++i) {
		if (vector_pop_str(&string_vector) != VECTOR_STATUS_OK) {
			printf("Error popping a string from vector_str at index %i\n", i);
			return 1;
		}
	}

	printf("Destroying vector_str instance...\n\n");
	vector_destroy_str(&string_vector);


	/**
	 * Vector int tests.
	 * Allocate MAX_ALLOCATE_PER_TEST ints.
	 * Pop MAX_ALLOCATE_PER_TEST ints.
	 * Destroy int vector.
	 */
	vector_init_int(&int_vector);
	printf("Allocating %i vector_int slots...\n", MAX_ALLOCATE_PER_TEST);
	for (int i=0; i<MAX_ALLOCATE_PER_TEST; ++i) {
		if (vector_push_int(&int_vector, i) != VECTOR_STATUS_OK) {
			printf("Error allocating an integer into vector_int at index %i\n",
				i);
			return 1;
		}
	}

	printf("vector_int:\tsize: %li\tidx: %li\n", int_vector.size,
		int_vector.idx);

	printf("Popping %i vector_int slots...\n", MAX_ALLOCATE_PER_TEST);
	for (int i=0; i<MAX_ALLOCATE_PER_TEST; ++i) {
		if (vector_pop_int(&int_vector) != VECTOR_STATUS_OK) {
			printf("Error popping an integer from vector_int at index %i\n", i);
			return 1;
		}
	}

	printf("Destroying vector_int instance...\n\n");
	vector_destroy_int(&int_vector);


	/**
	 * Vector uint tests.
	 * Allocate MAX_ALLOCATE_PER_TEST uints.
	 * Pop MAX_ALLOCATE_PER_TEST uints.
	 * Destroy uint vector.
	 */
	vector_init_uint(&uint_vector);
	printf("Allocating %i vector_uint slots...\n", MAX_ALLOCATE_PER_TEST);
	for (int i=0; i<MAX_ALLOCATE_PER_TEST; ++i) {
		if (vector_push_uint(&uint_vector, (unsigned int)i) !=
			VECTOR_STATUS_OK) {
			printf("Error allocating an unsigned integer into vector_uint at " \
				"index %i\n", i);
			return 1;
		}
	}

	printf("vector_uint:\tsize: %li\tidx: %li\n", uint_vector.size,
		uint_vector.idx);

	printf("Popping %i vector_uint slots...\n", MAX_ALLOCATE_PER_TEST);
	for (int i=0; i<MAX_ALLOCATE_PER_TEST; ++i) {
		if (vector_pop_uint(&uint_vector) != VECTOR_STATUS_OK) {
			printf("Error popping an unsigned integer from vector_uint at " \
				"index %i\n", i);
			return 1;
		}
	}

	printf("Destroying vector_uint instance...\n\n");
	vector_destroy_uint(&uint_vector);


	/**
	 * Vector long tests.
	 * Allocate MAX_ALLOCATE_PER_TEST longs.
	 * Pop MAX_ALLOCATE_PER_TEST longs.
	 * Destroy long vector.
	 */
	vector_init_long(&long_vector);
	printf("Allocating %i vector_long slots...\n", MAX_ALLOCATE_PER_TEST);
	for (int i=0; i<MAX_ALLOCATE_PER_TEST; ++i) {
		if (vector_push_long(&long_vector, (long)i) != VECTOR_STATUS_OK) {
			printf("Error allocating an long into vector_long at index %i\n",
				i);
			return 1;
		}
	}

	printf("vector_long:\tsize: %li\tidx: %li\n", long_vector.size,
		long_vector.idx);

	printf("Popping %i vector_long slots...\n", MAX_ALLOCATE_PER_TEST);
	for (int i=0; i<MAX_ALLOCATE_PER_TEST; ++i) {
		if (vector_pop_long(&long_vector) != VECTOR_STATUS_OK) {
			printf("Error popping an long from vector_long at index %i\n", i);
			return 1;
		}
	}

	printf("Destroying vector_long instance...\n\n");
	vector_destroy_long(&long_vector);


	/**
	 * Vector ulong tests.
	 * Allocate MAX_ALLOCATE_PER_TEST ulongs.
	 * Pop MAX_ALLOCATE_PER_TEST ulongs.
	 * Destroy ulong vector.
	 */
	vector_init_ulong(&ulong_vector);
	printf("Allocating %i vector_ulong slots...\n", MAX_ALLOCATE_PER_TEST);
	for (int i=0; i<MAX_ALLOCATE_PER_TEST; ++i) {
		if (vector_push_ulong(&ulong_vector, (unsigned long)i) !=
			VECTOR_STATUS_OK) {
			printf("Error allocating an unsigned long into vector_ulong at " \
				"index %i\n", i);
			return 1;
		}
	}

	printf("vector_ulong:\tsize: %li\tidx: %li\n", ulong_vector.size,
		ulong_vector.idx);

	printf("Popping %i vector_ulong slots...\n", MAX_ALLOCATE_PER_TEST);
	for (int i=0; i<MAX_ALLOCATE_PER_TEST; ++i) {
		if (vector_pop_ulong(&ulong_vector) != VECTOR_STATUS_OK) {
			printf("Error popping an unsigned long from vector_ulong at " \
				"index %i\n", i);
			return 1;
		}
	}

	printf("Destroying vector_ulong instance...\n\n");
	vector_destroy_ulong(&ulong_vector);


	/**
	 * Vector float tests.
	 * Allocate MAX_ALLOCATE_PER_TEST floats.
	 * Pop MAX_ALLOCATE_PER_TEST floats.
	 * Destroy float vector.
	 */
	vector_init_float(&float_vector);
	printf("Allocating %i vector_float slots...\n", MAX_ALLOCATE_PER_TEST);
	for (int i=0; i<MAX_ALLOCATE_PER_TEST; ++i) {
		if (vector_push_float(&float_vector, (float)i) != VECTOR_STATUS_OK) {
			printf("Error allocating a float into vector_float at index %i\n",
				i);
			return 1;
		}
	}

	printf("vector_float:\tsize: %li\tidx: %li\n", float_vector.size,
		float_vector.idx);

	printf("Popping %i vector_float slots...\n", MAX_ALLOCATE_PER_TEST);
	for (int i=0; i<MAX_ALLOCATE_PER_TEST; ++i) {
		if (vector_pop_float(&float_vector) != VECTOR_STATUS_OK) {
			printf("Error popping a float from vector_float at index %i\n", i);
			return 1;
		}
	}

	printf("Destroying vector_float instance...\n\n");
	vector_destroy_float(&float_vector);


	/**
	 * Vector double tests.
	 * Allocate MAX_ALLOCATE_PER_TEST doubles.
	 * Pop MAX_ALLOCATE_PER_TEST doubles.
	 * Destroy double vector.
	 */
	vector_init_double(&double_vector);
	printf("Allocating %i vector_double slots...\n", MAX_ALLOCATE_PER_TEST);
	for (int i=0; i<MAX_ALLOCATE_PER_TEST; ++i) {
		if (vector_push_double(&double_vector, (float)i) != VECTOR_STATUS_OK) {
			printf("Error allocating a double into vector_double at index %i\n",
				i);
			return 1;
		}
	}

	printf("vector_double:\tsize: %li\tidx: %li\n", double_vector.size,
		double_vector.idx);

	printf("Popping %i vector_double slots...\n", MAX_ALLOCATE_PER_TEST);
	for (int i=0; i<MAX_ALLOCATE_PER_TEST; ++i) {
		if (vector_pop_double(&double_vector) != VECTOR_STATUS_OK) {
			printf("Error popping a double from vector_double at index %i\n",
				i);
			return 1;
		}
	}

	printf("Destroying vector_double instance...\n\n");
	vector_destroy_double(&double_vector);


	/**
	 * Vector bool tests.
	 * Allocate MAX_ALLOCATE_PER_TEST bools.
	 * Pop MAX_ALLOCATE_PER_TEST bools.
	 * Destroy bool vector.
	 */
	vector_init_bool(&bool_vector);
	printf("Allocating %i vector_bool slots...\n", MAX_ALLOCATE_PER_TEST);
	for (int i=0; i<MAX_ALLOCATE_PER_TEST; ++i) {
		if (vector_push_bool(&bool_vector, (i % 2 == 0 ? true : false)) !=
			VECTOR_STATUS_OK) {
			printf("Error allocating a bool into vector_bool at index %i\n", i);
			return 1;
		}
	}

	printf("vector_bool:\tsize: %li\tidx: %li\n", bool_vector.size,
		bool_vector.idx);

	printf("Popping %i vector_bool slots...\n", MAX_ALLOCATE_PER_TEST);
	for (int i=0; i<MAX_ALLOCATE_PER_TEST; ++i) {
		if (vector_pop_bool(&bool_vector) != VECTOR_STATUS_OK) {
			printf("Error popping a bool from vector_bool at index %i\n", i);
			return 1;
		}
	}

	printf("Destroying vector_bool instance...\n\n");
	vector_destroy_bool(&bool_vector);


	return 0;

}
