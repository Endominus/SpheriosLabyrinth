// Computes fragment colors for the model triangles.
uniform vec3 ballPos;
uniform vec3 viewerPos;
uniform float elapsedTime;  //time in seconds since simulation began

varying vec3 normal;
varying vec4 vertex;
uniform vec3 lightPos;

void main()
{
	//vec4 lightVec = normalize(vec4(ballPos[0] - vertex[0], ballPos[1] - vertex[1], ballPos[2] - vertex[2], 0));
	//vec3 lightVec = vec3(ballPos[0] - vertex[0], ballPos[1] - vertex[1], ballPos[2] - vertex[2]);
	//float shadingFactor = (10.0*dot(normalize(lightVec), normal)/dot(lightVec, lightVec))+1;
	//gl_FragColor = vec4(gl_Color[0]*shadingFactor, gl_Color[1]*shadingFactor, gl_Color[2]*shadingFactor, 1);
	float ballRed = 0.7 + 0.3 * sin( 2* elapsedTime );
	float ballGreen = 0.7 + 0.3 * sin( 1.2* elapsedTime + 0.5 );
	float ballBlue = 0.7 + 0.3 * sin( 1.8* elapsedTime + 0.2 );
	gl_FragColor = vec4(ballRed, ballGreen, ballBlue, 1);
	//gl_FragColor = gl_Color;
}
