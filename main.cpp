#include "includes/buffer.h"
#include "includes/core.h"
#include "includes/font.h"
#include "includes/screen.h"
#include "includes/shader.h"
#include "includes/texture.h"
#include "includes/window.h"

using namespace GeoFrame;

int main() {
	Init();
	Window window(3000, 1500, "Test window");

	TextureSettings setting;
	setting.mSRGBLoading = false;
	Texture tex("C:/Users/Mr.W/Pictures/IPCONFIG.png", setting);

	Source vertex(SourceType::VERTEX_SHADER);
	vertex.LoadBuffer(
		"\
#version 330 core\n\
layout(location = 0) in vec3 iPosition;\n\
layout(location = 1) in vec2 iTexpos;\n\
out vec2 fTexpos;\n\
\n\
void main() {\n\
	gl_Position = vec4(iPosition, 1.0f);\n\
	fTexpos = iTexpos;\n\
}\
		"
	);
	vertex.Compile();

	Source fragment(SourceType::FRAGMENT_SHADER);
	fragment.LoadBuffer(
		"\
#version 330 core\n\
in vec2 fTexpos;\n\
out vec4 FragColor;\n\
\n\
uniform sampler2D tex;\n\
\n\
void main() {\n\
	vec3 color = texture(tex, fTexpos).rgb;\n\
	FragColor = vec4(color, 1.0f);\n\
}\
"
);
	fragment.Compile();

	Program program(vertex, fragment);
	program.Link();

	std::vector<float> posData = {
		-0.5, -0.5, 0.0, 0.0, 0.0,
		0.5, -0.5, 0.0, 1.0, 0.0,
		0.5, 0.5, 0.0, 1.0, 1.0,
		-0.5, 0.5, 0.0, 0.0, 1.0
	};
	std::vector<unsigned> indexData = {
		0, 1, 2,
		2, 3, 0
	};


	VertexBuffer<float> vert(BufferType::ARRAY_BUFFER);
	vert.SetAttribute(Attribute(GLType::FLOAT, 3));
	vert.SetAttribute(Attribute(GLType::FLOAT, 2));
	vert.SetBufferData(posData);

	VertexBuffer<unsigned> indx(BufferType::ELEMENT_BUFFER);
	indx.SetBufferData(indexData);

	VertexArray vao;
	vao.Register(vert);
	vao.Register(indx);

	Screen target(3000, 1500);
	target.AttachBuffer();

	MultisampleScreen screen(3000, 1500, 4);
	screen.AttachBuffer();

	Font font("C:/Windows/Fonts/yumin.ttf", 250);
	font.RegisterChar(L'‚ ');
	Character c = font.GetCharData(L'‚ ');

	while (true) {
		glfwPollEvents();

		window.Fill({ 0, 0, 0 });
		window.Clear();

		if (window.IsClosed()) { break; }
		else { ; }

		screen.Bind();
		program.Use();
		program.SetInteger("tex", 0);
		glActiveTexture((GLenum)TextureTargets::TEX_1);
		//tex.Bind();
		c.charTex.Bind();
		vao.Draw();
		c.charTex.Unbind();
		//tex.Unbind();
		screen.Unbind();

		screen.Blit(target);
		window.SetCurrent();
		//glBindFramebuffer(GL_DRAW_FRAMEBUFFER, 0);
		//scr.ReadOnlyBind();
		//glBlitFramebuffer(0, 0, 3000, 1500, 0, 0, 3000, 1500, GL_COLOR_BUFFER_BIT, GL_LINEAR);
		Texture fbo = target[0];
		program.Use();
		fbo.Bind();
		vao.Draw();
		fbo.Unbind();

		window.Swap();
	}


	GeoFrame::Terminate();

	return 0;
}