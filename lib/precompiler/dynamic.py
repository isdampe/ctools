class Dynamic:

	def __init__(self, name, types):
		self.name = name
		self.types = types
		self.dynamicHeaderBuffer = ""
		self.dynamicBodyBuffer = ""
		self.headerBuffer = ""
		self.bodyBuffer = ""

	def preCompileDynamicHeader(self):
		with open("src/dynamic/dynamic-" + self.name + ".h", "r") as fh:
			data = fh.read()
			self.dynamicHeaderBuffer = self._generateBuffer(data, self.types)
		if not self.dynamicHeaderBuffer:
			print("Error reading src/dynamic/dynamic-" + self.name + ".h")
			exit(1)

	def preCompileHeader(self):
		template = False
		with open("src/" + self.name + ".h", "r") as fh:
			template = fh.read()
			self.headerBuffer = template
		if not template:
			print("Error reading src/" + self.name + ".h")
			exit(1)

	def preCompileDynamicBody(self):
		with open("src/dynamic/dynamic-" + self.name + ".c", "r") as fh:
			data = fh.read()
			self.dynamicBodyBuffer = self._generateBuffer(data, self.types)
		if not self.dynamicBodyBuffer:
			print("Error reading src/dynamic/dynamic-" + self.name + ".c")
			exit(1)

	def preCompileBody(self):
		template = False
		with open("src/" + self.name + ".c", "r") as fh:
			template = fh.read()
			self.bodyBuffer = template
		if not template:
			print("Error reading src/" + self.name + ".c")
			exit(1)

	def preCompile(self):
		self.preCompileDynamicHeader()
		self.preCompileDynamicBody()
		self.preCompileHeader()
		self.preCompileBody()
		header = self._appendBuffer(self.headerBuffer, self.dynamicHeaderBuffer)
		body = self._appendBuffer(self.bodyBuffer, self.dynamicBodyBuffer)

		with open("../" + self.name + ".c", "w") as fh:
			fh.write(body)
			print("Wrote to ../" + self.name + ".c")

		with open("../" + self.name + ".h", "w") as fh:
			fh.write(header)
			print("Wrote to ../" + self.name + ".h")

	def _appendBuffer(self, template, buffer):
		outbuffer = ""
		for line in template.split("\n"):
			if line == "//<DYNAMIC_ENTRIES>":
				outbuffer += buffer + "\n"
			else:
				outbuffer += line + "\n"

		return outbuffer

	def _generateBuffer(self, data, types):
		buffers = []
		originalData = data
		for t in types:
			data = data.replace("<TYPE>", t[0])
			data = data.replace("<UPPER_TYPE>", t[0].upper())
			data = data.replace("<INPUT_TYPE>", t[1])
			buffers.append(data)
			data = originalData
		return "\n\n".join(buffers)
