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
struct lightpoint{
	float constant;
	float liner;
	float quadratic;
};

struct lightspot{
	float  cosphy;
};
uniform lightspot lights;
uniform lightpoint lightp;
uniform Material material;
//uniform sampler2D ourTexture;
//uniform sampler2D ourTexture2;

uniform vec3 lightpos;
uniform vec3 lightcolor;
uniform vec3 objcolor;
uniform vec3 ambientcolor;
uniform vec3 camerapos;
uniform  vec3 lightDirUniform;

out vec4 color;
void main()
{
	float dist = length(lightpos - Fragpos);
	float attenuation = 1.0f /(lightp.constant +lightp.liner *dist + lightp.quadratic*(dist*dist) );
  	
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
	vec3 ambient =  texture(material.diffuse, TexCoord).rgb + ambientcolor;
   vec3  dd= diffuse * attenuation + specular *attenuation;

	vec3 comband = (ambient + dd )*objcolor;
	vec3 fl = normalize( Fragpos - lightpos );
	float costheta = dot(fl, lightDirUniform);
	if(costheta < lights.cosphy )
	{
		color = vec4((ambient + (diffuse + specular)*objcolor) ,1.0);
	}else
	{
		color = vec4( ambient*objcolor,1.0);
	}

	
}