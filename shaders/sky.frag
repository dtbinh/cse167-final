#version 120

uniform samplerCube CubeMap;
//uniform sampler2D texture1;
//varying vec2 vTexCoord;

void main()
{
	gl_FragColor = textureCube(CubeMap, gl_TexCoord[0].stp);
	//gl_FragColor = texture2D(texture1, gl_TexCoord[0].st);
	//gl_FragColor = texture2D(texture1, vTexCoord);
	
}
