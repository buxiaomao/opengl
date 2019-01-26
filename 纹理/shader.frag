#version 330 core

in vec3 Fragpos;
in vec3 Normal;
in vec2 TexCoord; 
struct Material{
	vec3 ambient;
	sampler2D diffuse;
	sampler2D specular;
	float shinness;
};

uniform Material material;
//uniform sampler2D ourTexture;
//uniform sampler2D ourTexture2;

uniform vec3 lightpos;
uniform vec3 lightcolor;
// 物体颜色
uniform vec3 objcolor;


uniform vec3 ambientcolor;
uniform vec3 camerapos;

out vec4 color;
void main()
{
	
	vec3 lightDir  = normalize(lightpos - Fragpos);
	vec3 reflectvec = reflect(-lightDir, Normal);
	vec3 cameravec = normalize(camerapos - Fragpos);
	float specularamount = pow(dot (reflectvec, cameravec),material.shinness);
	


	//Specular 镜面反射贴图+ 物体本身镜面反射。
	vec3 specular = texture(material.specular, TexCoord).rgb* specularamount *lightcolor;
	
	// diffuse 漫反射贴图+物体本身漫反射。
	vec3 diffuse = texture(material.diffuse, TexCoord).rgb+ max(dot(lightDir, Normal),0) * lightcolor;
	//vec3 diffuse= texture(material.diffuse, TexCoord).rgb;
	// ambient 环境光照。。
	vec3 ambient =  ambientcolor;

	vec3 comband = (ambient + diffuse + specular)*objcolor;
	color = vec4(comband ,1.0);
	
}