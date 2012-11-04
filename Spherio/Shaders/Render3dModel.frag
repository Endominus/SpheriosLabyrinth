// Computes fragment colors for the model triangles.
uniform mat4 projMatrix;  //projection matrix
uniform mat4 viewMatrix;  //view matrix (camera)

varying vec4 normal;
varying vec4 vertex;
uniform vec3 lightPos;

void main()
{
	//vec4 lightVec = normalize(vec4(lightPos[0] - vertex[0], lightPos[1] - vertex[1], lightPos[2] - vertex[2], 0));
	vec4 lightVec = vec4(lightPos[0] - vertex[0], lightPos[1] - vertex[1], lightPos[2] - vertex[2], 0);
	float shadingFactor = dot(normalize(lightVec), normal)/dot(lightVec, lightVec);
	gl_FragColor = vec4(gl_Color[0]*shadingFactor, gl_Color[1]*shadingFactor, gl_Color[2]*shadingFactor, 1);
	//gl_FragColor = vec4(1, 0, 0, 1);
}
