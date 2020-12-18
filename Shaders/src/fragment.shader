#version 330 core

in vec2 texCoord;

layout(location = 0) out vec4 color;

uniform vec4 u_Color;
uniform sampler2D u_Texture;

void main(){
	vec4 texColor = texture(u_Texture, texCoords)
	color = texColor;
}