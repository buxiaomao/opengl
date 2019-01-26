#version 330 core

in vec3 Fragpos;
in vec3 Normal;
in vec2 TexCoord; 
struct Material{
	vec3 ambient;
	sampler2D diffuse;
	vec3 specular;
	float shinness;
};

uniform Material material;
//uniform sampler2D ourTexture;
//uniform sampler2D ourTexture2;

uniform vec3 lightpos;
uniform vec3 lightcolor;
// ÎïÌåÑÕÉ«
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
	


	//Specular
	vec3 specular =material.specular* specularamount *lightcolor;
	
	// diffuse 
	vec3 diffuse = texture(material.diffuse, TexCoord).rgb+ max(dot(lightDir, Normal),0) * lightcolor;
	//vec3 diffuse= texture(material.diffuse, TexCoord).rgb;
	// ambient
	vec3 ambient = texture(material.diffuse, TexCoord).rgb * ambientcolor;

	vec3 comband = (ambient + diffuse + specular)*objcolor;
	color = vec4(comband ,1.0);
	
}