#version 330 core

in vec3 Fragpos;
in vec3 Normal;

struct Material{
	vec3 ambient;
	vec3 diffuse;
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
	vec3 diffuse = material.diffuse *  max(dot(lightDir, Normal),0) * lightcolor;
	// ambient
	vec3 ambient =material.ambient * ambientcolor;

	vec3 comband = (ambient + diffuse + specular)*objcolor;
	color = vec4(comband ,1.0);
	
}