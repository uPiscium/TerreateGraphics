#include "buffer.h"
#include "core.h"
#include "shader.h"
#include "window.h"

using namespace GeoFrame;

int main() {
	Init();
	Window window(1500, 750, "Test window");
	Source vertex(SourceType::VERTEX_SHADER);
	vertex.LoadBuffer(
		"\
#version 330 core\n\
layout(location = 0) in vec3 position;\n\
\n\
void main() {\n\
	gl_Position = vec4(position, 1.0f);\n\
}\
		"
	);
	vertex.Compile();

	Source fragment(SourceType::FRAGMENT_SHADER);
	fragment.LoadBuffer(
		"\
#version 330 core\n\
out vec4 FragColor;\n\
\n\
void main() {\n\
	FragColor = vec4(1.0f);\n\
}\
"
	);
	fragment.Compile();

	Program program(vertex, fragment);
	program.Link();

	std::vector<float> posData = {
		-0.5, -0.5,
		0.5, -0.5,
		0.0, 0.5
	};
	std::vector<unsigned> indexData = {
		0, 1, 2
	};


	VertexBuffer<float> vert(BufferType::ARRAY_BUFFER, BufferUsage::STATIC_DRAW);
	vert.SetAttribute(Attribute(GLType::FLOAT, 2));
	vert.SetBufferData(posData);

	VertexBuffer<unsigned> indx(BufferType::ELEMENT_BUFFER, BufferUsage::STATIC_DRAW);
	indx.SetBufferData(indexData);

	VertexArray vao;
	vao.Register(vert);
	vao.Register(indx);


	window.SetCurrent();
	while (true) {
		glfwPollEvents();

		window.Fill({ 1, 0, 0 });
		window.Clear();
		
		if (window.IsClosed()) { break; }
		else { ; }

		program.Use();
		vao.Draw();

		window.Swap();
	}

	Terminate();
	
	return 0;
}