#version 330 core

layout (location = 0) in vec3 in_Position;
layout (location = 1) in vec3 in_Normal;
layout (location = 2) in int in_Material;

uniform mat4 u_ProjectionMatrix;
uniform mat4 u_ViewMatrix;
uniform mat4 u_ModelMatrix;

out DATA
{
	vec3 position;
	vec3 normal;
	flat int material;
} vs_out;

void main()
{
	vs_out.position = vec3(u_ModelMatrix * vec4(in_Position, 1.0));
	vs_out.normal = mat3(transpose(inverse(u_ModelMatrix))) * in_Normal;
	vs_out.material = in_Material;

	gl_Position = u_ProjectionMatrix * u_ViewMatrix * vec4(vs_out.position, 1.0);
};
