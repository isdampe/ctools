from dynamic import Dynamic

vector = Dynamic("vector", types = [
		("int", "int"),
		("uint", "unsigned int"),
		("long", "long"),
		("ulong", "unsigned long"),
		("float", "float"),
		("double", "double"),
		("bool", "bool")
	])

vector.preCompile()

hashmap = Dynamic("hashmap", types = [
		("byte", "char"),
		("int", "int"),
		("uint", "unsigned int"),
		("long", "long"),
		("ulong", "unsigned long"),
		("float", "float"),
		("double", "double"),
		("bool", "bool")
	])

hashmap.preCompile()

