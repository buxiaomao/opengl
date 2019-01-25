#version 330 core
out vec4 color;

in vec3 Fragpos;
in vec3 Normal;

//uniform sampler2D ourTexture;
//uniform sampler2D ourTexture2;

uniform vec3 lightpos;
uniform vec3 lightcolor;
// 物体颜色
uniform vec3 objcolor;
// 环境颜色
uniform vec3 ambientcolor;
void main()
{
	// diffuse计算
	vec3 norm = normalize(Normal);
	vec3 lightDir  = normalize(lightpos - Fragpos);
	float diff = dot(lightDir, norm);
	vec3 diffuse = diff * lightcolor;

	color = vec4(diffuse,1.0);
	//color = vec4(objcolor*ambientcolor ,1.0)*texture(ourTexture, TexCoord)*texture(ourTexture2, TexCoord);
   // color = texture(ourTexture, TexCoord)*texture(ourTexture2, TexCoord);
}