//#version 130
// Computes fragment colors for the model triangles.

uniform vec3 ballPos;
uniform float elapsedTime;  //time in seconds since simulation began

varying vec3 normal;
varying vec4 vertex;
uniform vec3 lightPos;

void main()
{
	//vec4 lightVec = normalize(vec4(ballPos[0] - vertex[0], ballPos[1] - vertex[1], ballPos[2] - vertex[2], 0));
	vec3 lightVec = vec3(ballPos[0] - vertex[0], ballPos[1] - vertex[1], ballPos[2] - vertex[2]);
	float b = 5.0*dot(normalize(lightVec), normal)/dot(lightVec, lightVec);
	float a = max(b, 0.0);
	float shadingFactor = (a + 0.1);
	float ballRed = 0.7 + 0.3 * sin( 2* elapsedTime );
	float ballGreen = 0.7 + 0.3 * sin( 1.2* elapsedTime + 0.5 );
	float ballBlue = 0.7 + 0.3 * sin( 1.8* elapsedTime + 0.2 );
	gl_FragColor = vec4(gl_Color[0]*ballRed*shadingFactor,
						gl_Color[1]*ballGreen*shadingFactor, 
						gl_Color[2]*ballBlue*shadingFactor, 1);
	//gl_FragColor = vec4(1, 0, 0, 1);
	//gl_FragColor = gl_Color;
}
