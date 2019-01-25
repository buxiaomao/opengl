#version 330 core
in vec3 ourColor;
in vec2 TexCoord;
out vec4 color;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;
// ������ɫ
uniform vec3 objcolor;
// ������ɫ
uniform vec3 ambientcolor;
void main()
{
	color = vec4(objcolor*ambientcolor ,1.0)*texture(ourTexture, TexCoord)*texture(ourTexture2, TexCoord);
   // color = texture(ourTexture, TexCoord)*texture(ourTexture2, TexCoord);
}