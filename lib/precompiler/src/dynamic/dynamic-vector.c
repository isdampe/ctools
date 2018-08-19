VECTOR_STATUS vector_init_<TYPE>(struct vector_<TYPE> *vector)
{
	vector->size = 100;
	vector->idx = 0;
	vector->data = calloc(vector->size, sizeof(<INPUT_TYPE>));

	return (!vector->data ? VECTOR_STATUS_ERR_ALLOC : VECTOR_STATUS_OK);
}

VECTOR_STATUS vector_push_<TYPE>(struct vector_<TYPE> *vector,
	const <INPUT_TYPE> src)
{
	vector->data[vector->idx++] = src;

	if (vector->idx == vector->size) {
		VECTOR_STATUS result = vector_auto_expand_<TYPE>(vector);
		if (result != VECTOR_STATUS_OK)
			return result;
	}

	return VECTOR_STATUS_OK;
}

VECTOR_STATUS vector_prepend_<TYPE>(struct vector_<TYPE> *vector,
	const <INPUT_TYPE> src)
{
	VECTOR_STATUS result = vector_push_<TYPE>(vector, src);
	<INPUT_TYPE> tmp = vector->data[0];
	vector->data[0] = vector->data[vector->idx];
	vector->data[vector->idx] = tmp;

	return result;
}

static VECTOR_STATUS vector_auto_expand_<TYPE>(struct vector_<TYPE> *vector)
{
	vector->size += VECTOR_MAX_EXPAND_STEP;
	vector->data = realloc(vector->data, vector->size * sizeof(<INPUT_TYPE>));

	return (!vector->data ? VECTOR_STATUS_ERR_ALLOC : VECTOR_STATUS_OK);
}

long vector_search_<TYPE>(struct vector_<TYPE> *vector, const <INPUT_TYPE> src)
{
	for (long i=0; i<vector->idx; ++i)
		if (vector->data[i] == src)
			return i;

	return -1;
}

VECTOR_STATUS vector_pop_<TYPE>(struct vector_<TYPE> *vector)
{
	if (vector->idx == 0)
		return VECTOR_STATUS_ERR_UNDERFLOW;

	vector->data[--vector->idx] = 0;
	if (vector->size - vector->idx > (2 * VECTOR_MAX_EXPAND_STEP)) {
		VECTOR_STATUS result = vector_auto_shrink_<TYPE>(vector);
		if (result != VECTOR_STATUS_OK)
			return result;
	}

	return VECTOR_STATUS_OK;
}

VECTOR_STATUS vector_pop_front_<TYPE>(struct vector_<TYPE> *vector)
{
	vector->data[0] = vector->data[vector->idx];
	return vector_pop_<TYPE>(vector);
}

static VECTOR_STATUS vector_auto_shrink_<TYPE>(struct vector_<TYPE> *vector)
{
	vector->size -= VECTOR_MAX_EXPAND_STEP;
	vector->data = realloc(vector->data, vector->size * sizeof(<INPUT_TYPE>));

	return (!vector->data ? VECTOR_STATUS_ERR_ALLOC : VECTOR_STATUS_OK);
}

void vector_destroy_<TYPE>(struct vector_<TYPE> *vector)
{
	free(vector->data);
}
