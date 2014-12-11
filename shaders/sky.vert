#version 120

uniform vec3 CameraPosition;
//varying vec2 vTexCoord;
void main()
{
	gl_TexCoord[0].stp = vec3(gl_Vertex.x, gl_Vertex.y, -gl_Vertex.z);
	//vTexCoord = gl_MultiTexCoord0.xy;
	gl_Position = gl_ModelViewProjectionMatrix * vec4(gl_Vertex.xyz + CameraPosition, 1.0);
	//gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;
}
