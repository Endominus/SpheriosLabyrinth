// Computes fragment colors for the model triangles.
uniform vec3 ballPos;

varying vec3 normal;
varying vec4 vertex;
uniform vec3 lightPos;

void main()
{
	//vec4 lightVec = normalize(vec4(ballPos[0] - vertex[0], ballPos[1] - vertex[1], ballPos[2] - vertex[2], 0));
	//vec3 lightVec = vec3(ballPos[0] - vertex[0], ballPos[1] - vertex[1], ballPos[2] - vertex[2]);
	//float shadingFactor = (10.0*dot(normalize(lightVec), normal)/dot(lightVec, lightVec))+1;
	//gl_FragColor = vec4(gl_Color[0]*shadingFactor, gl_Color[1]*shadingFactor, gl_Color[2]*shadingFactor, 1);
	gl_FragColor = vec4(1, 1, 1, 1);
	//gl_FragColor = gl_Color;
}
