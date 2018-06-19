struct vector_<TYPE> {
	long size;
	long idx;
	<INPUT_TYPE> *data;
};

VECTOR_STATUS vector_init_<TYPE>(struct vector_<TYPE> *vector);
VECTOR_STATUS vector_push_<TYPE>(struct vector_<TYPE> *vector, const <INPUT_TYPE> src);
VECTOR_STATUS vector_prepend_<TYPE>(struct vector_<TYPE> *vector, const <INPUT_TYPE> src);
static VECTOR_STATUS vector_auto_expand_<TYPE>(struct vector_<TYPE> *vector);
long vector_search_<TYPE>(struct vector_<TYPE> *vector, const <INPUT_TYPE> src);
VECTOR_STATUS vector_pop_<TYPE>(struct vector_<TYPE> *vector);
static VECTOR_STATUS vector_auto_shrink_<TYPE>(struct vector_<TYPE> *vector);
void vector_destroy_<TYPE>(struct vector_<TYPE> *vector);
