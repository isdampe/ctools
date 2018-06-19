import os

def main():
	types = [
		("int", "int"),
		("uint", "unsigned int"),
		("long", "long"),
		("ulong", "unsigned long"),
		("float", "float"),
		("double", "double"),
		("bool", "bool")
	]

	# Signatures

	buffer = False

	with open("src/dynamic-signatures.h", "r") as fh:
		data = fh.read()
		buffer = generate_buffer(data, types)

	if not buffer:
		print("Error reading dynamic-signatures.h")
		exit(1)

	template = False
	with open("src/vector.h", "r") as fh:
		template = fh.read()

	if not template:
		print("Error reading vector.h")
		exit(1)

	signature_buffer = append_buffer(template, buffer)


	# Vectors

	buffer = False

	with open("src/dynamic-vector.c", "r") as fh:
		data = fh.read()
		buffer = generate_buffer(data, types)

	if not buffer:
		print("Error reading dynamic-vector.h")
		exit(1)

	template = False
	with open("src/vector.c", "r") as fh:
		template = fh.read()

	if not template:
		print("Error reading vector.h")
		exit(1)

	vector_buffer = append_buffer(template, buffer)

	with open("../vector.c", "w") as fh:
		fh.write(vector_buffer)
		fh.close()

	with open("../vector.h", "w") as fh:
		fh.write(signature_buffer)
		fh.close()

	print("Wrote to ../vector.c and ../vector.h")

def generate_buffer(data, types):
	buffers = []
	originalData = data
	for t in types:
		data = data.replace("<TYPE>", t[0])
		data = data.replace("<INPUT_TYPE>", t[1])
		buffers.append(data)
		data = originalData

	return "\n\n".join(buffers)

def append_buffer(template, buffer):
	outbuffer = ""
	for line in template.split("\n"):
		if line == "//<DYNAMIC_ENTRIES>":
			outbuffer += buffer + "\n"
		else:
			outbuffer += line + "\n"

	return outbuffer


if __name__ == "__main__":
	main()
