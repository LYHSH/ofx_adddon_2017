#include "spreadSwitcher.h"

#define GLSL120(shader)  "#version 120 \n #extension GL_ARB_texture_rectangle : enable \n" #shader
spreadSwitcher::spreadSwitcher(void)
{
}


spreadSwitcher::~spreadSwitcher(void)
{
}

bool spreadSwitcher::initGlsl()
{
	bool res = true;
	vertex = GLSL120(
		void main()
	{
		vec4 pos = gl_ModelViewProjectionMatrix * gl_Vertex;

		gl_Position = pos;
		gl_TexCoord[0] = gl_MultiTexCoord0;
		gl_FrontColor = gl_Color;
	}
	);

	fragment = GLSL120(
		uniform sampler2DRect tex0;
	uniform sampler2DRect maskTex;
	void main(){
		vec2 pos = gl_TexCoord[0].st;
		vec3 src = texture2DRect(tex0, pos).rgb;
		float mask = texture2DRect(maskTex, pos).r;
		gl_FragColor = vec4( src , mask);
	}
	);

	res &= shader.setupShaderFromSource(GL_VERTEX_SHADER, vertex);
	res &= shader.setupShaderFromSource(GL_FRAGMENT_SHADER, fragment);
	res &= shader.bindDefaults();
	res &= shader.linkProgram();

	return res;
}
