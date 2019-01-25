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
uniform vec3 camerapos;
void main()
{
	// diffuse计算
	vec3 lightDir  = normalize(lightpos - Fragpos);
	vec3 diffuse = max(dot(lightDir, Normal),0) * lightcolor;

	// Specular
	vec3 reflectvec = reflect(-lightDir, Normal);
	vec3 cameravec = normalize(camerapos - Fragpos);
	float specularamount = pow(dot (reflectvec, cameravec),32);
	vec3 specular = specularamount *lightcolor;


	vec3 comband = (diffuse +ambientcolor + specular)*objcolor;
	color = vec4(comband ,1.0);
	
}