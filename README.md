# C Tools

Some various tool libraries that are useful for reuse.

## Simple C vector library

`lib/vector.h` defines a simple dynamic array library. Available types include

* str (string, or char \*)
* int
* uint (unsigned int)
* long
* ulong (unsigned long)
* float
* double
* bool

All method signatures are identical, less their type and appended type name.

Initialise a vector like so

```c
struct vector_[type] some_vector;

if (vector_init_[type](&some_vector) != VECTOR_STATUS_OK) {
	//Error
}
```

Push to a vector like so

```c
vector_push_[type](&some_vector, [some_value]);
```

Destroy a vector like so

```c
vector_destroy_[type](&some_vector);
```

### Basic example using strings

A simple example where `type` is `str`

```c
#include <stdio.h>
#include "vector.h"

int main()
{
	struct vector_str some_vector;

	if (vector_init_str(&some_vector) != VECTOR_STATUS_OK)
		return 1;

	vector_push_str(&some_vector, "Hello world");
	vector_push_str(&some_vector, "Today it is raining");
	vector_push_str(&some_vector, "Tomorrow it will not");

	printf("%s\n", some_vector.data[0]); // Hello world
	printf("%s\n", some_vector.data[1]); // Today it is raining
	printf("%s\n", some_vector.data[2]); // Tomorrow it will not
	printf("%li\n", some_vector.size); //3

	vector_pop_str(&some_vector);
	printf("%li\n", some_vector.size); //2

	vector_prepend_str(&some_vector, "Foo bar");
	printf("%s\n", some_vector.data[0]); // Foo bar

	long search_idx = vector_search_str(&some_vector, "Today it is raining");
	if (search_idx < 0)
		printf("Result not found\n");
	else
		printf("Match found at index %li, value: %s\n", search_idx, some_vector.data[search_idx]);

	vector_destroy_str(&some_vector);
}
```

### Further examples

See `examples/`
