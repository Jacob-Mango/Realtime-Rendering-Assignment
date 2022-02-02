#version 330 core

out vec4 FragColor;

in DATA
{
	vec3 position;
	vec3 normal;
	flat int material;
} fs_in;

struct DirectionalLight
{
	vec3 direction;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct PointLight
{
	vec3 position;
	
	float constant;
	float linear;
	float quadratic;
	
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
}; 

uniform vec3 u_CameraPosition;
uniform DirectionalLight u_DirectionalLight;
uniform PointLight u_PointLights[7];
uniform int u_NumPointLights;

uniform int u_LightingEnabled;

// 6 materials for 6 faces
uniform Material u_Materials[6];

vec3 ApplyDirectionalLight(DirectionalLight light, Material material, vec3 normal, vec3 view)
{
	float diff = max(dot(normal, -light.direction), 0.0);

	vec3 halfwayDir = normalize(-light.direction + view);  
	float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);

	vec3 ambient = light.ambient * material.diffuse;
	vec3 diffuse = light.diffuse * diff * material.diffuse;
	vec3 specular = light.specular * spec * material.specular;
	return ambient + diffuse + specular;
};

vec3 ApplyPointLight(PointLight light, Material material, vec3 normal, vec3 view)
{
	vec3 direction = normalize(light.position - fs_in.position);

	float diff = max(dot(normal, direction), 0.0);

	vec3 halfwayDir = normalize(direction + view);  
	float spec = pow(max(dot(normal, halfwayDir), 0.0), material.shininess);

	float distance = length(light.position - fs_in.position);
	float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));	

	vec3 ambient = light.ambient * attenuation * material.ambient;
	vec3 diffuse = light.diffuse * attenuation * diff * material.diffuse;
	vec3 specular = light.specular * attenuation * spec * material.specular;
	return ambient + diffuse + specular;
};

void main()
{
	vec3 view = normalize(u_CameraPosition - fs_in.position);
	Material material = u_Materials[fs_in.material];

	vec3 result;

	if (u_LightingEnabled == 1)
	{
		result += ApplyDirectionalLight(u_DirectionalLight, material, fs_in.normal, view);
		for (int i = 0; i < u_NumPointLights; i++)
			result += ApplyPointLight(u_PointLights[i], material, fs_in.normal, view);
	}
	else
	{
		result = material.ambient + material.diffuse;
	}

	FragColor = vec4(result, 1.0);
};
