//#version 130
// Computes fragment colors for the model triangles.

uniform vec3 ballPos;
uniform vec3 viewerPos;
uniform float elapsedTime;  //time in seconds since simulation began
uniform sampler2D texId; //this is the texture unit that has the rendered image
uniform mat4 shadowMatrix;

varying float index;
varying vec3 normal;
varying vec4 vertex;
uniform vec3 lightPos;

vec3 getColorFromIndex(int index) {
	switch(index) {
		case 0:
//			return 255*256*256+0*256+0;
			return vec3(1,0,0);
		case 1:
//			return 255*256*256+255*256+0;
			return vec3(1,1,0);
		case 2:
//			return 0*256*256+255*256+0;
			return vec3(0,1,0);
		case 3:
//			return 0*256*256+255*256+255;
			return vec3(0,1,1);
		case 4:
//			return 0*256*256+0*256+255;
			return vec3(0,0,1);
		default:
			return vec3(1,1,1);
	}
}

bool areEqual(vec3 v1, vec3 v2) {
	if(abs(v1[0]-v2[0])<0.1 && abs(v1[1]-v2[1])<0.1 && abs(v1[2]-v2[2])<0.1)
		return true;
	return false;
}

void main()
{
	shadowMatrix[0][0] = -1;
	shadowMatrix[0][1] = 0;
	shadowMatrix[0][2] = 0;
	shadowMatrix[0][3] = 0;
	shadowMatrix[1][0] = 0;
	shadowMatrix[1][1] = 1;
	shadowMatrix[1][2] = 0;
	shadowMatrix[1][3] = -0.81;
	shadowMatrix[2][0] = 0;
	shadowMatrix[2][1] = 0;
	shadowMatrix[2][2] = -1;
	shadowMatrix[2][3] = 0;
	shadowMatrix[3][0] = 0;
	shadowMatrix[3][1] = 0;
	shadowMatrix[3][2] = 0;
	shadowMatrix[3][3] = 1;
	//vec4 lightVec = normalize(vec4(ballPos[0] - vertex[0], ballPos[1] - vertex[1], ballPos[2] - vertex[2], 0));
	vec3 lightVec = vec3(ballPos[0] - vertex[0], ballPos[1] - vertex[1], ballPos[2] - vertex[2]);
	float b = 5.0*dot(normalize(lightVec), normal)/dot(lightVec, lightVec);
	float a = max(b, 0.0);
	if((vertex[2]-ballPos[2])>max(abs(vertex[1]-ballPos[1]),abs(vertex[0]-ballPos[0]))) {
		vec4 temp = shadowMatrix*vertex;
		temp[0] = temp[0]*512+512;
		temp[1] = temp[1]*512+512;
		if(!areEqual(getColorFromIndex(index),texture2D(texId,temp)))
			a = 0;
//		if(min(temp[1],temp[0])>511.99 && max(temp[0],temp[1])<512.01)
/*		if(shadowMatrix[0][0] == 0 && 
			shadowMatrix[0][1] == 0 && 
			shadowMatrix[0][2] == 0 && 
			shadowMatrix[0][3] == 0 && 
			shadowMatrix[1][0] == 0 && 
			shadowMatrix[1][1] == 0 && 
			shadowMatrix[1][2] == 0 && 
			shadowMatrix[1][3] == 0 && 
			shadowMatrix[2][0] == 0 && 
			shadowMatrix[2][1] == 0 && 
			shadowMatrix[2][2] == 0 && 
			shadowMatrix[2][3] == 0 && 
			shadowMatrix[3][0] == 0 && 
			shadowMatrix[3][1] == 0 && 
			shadowMatrix[3][2] == 0 && 
			shadowMatrix[3][3] == 0)*/
		if(index<1)
			a=1;
	}
	float shadingFactor = (a + 0.01);
	float ballRed = 0.7 + 0.3 * sin( 2* elapsedTime );
	float ballGreen = 0.7 + 0.3 * sin( 1.2* elapsedTime + 0.5 );
	float ballBlue = 0.7 + 0.3 * sin( 1.8* elapsedTime + 0.2 );
	gl_FragColor = vec4(gl_Color[0]*ballRed*shadingFactor,
						gl_Color[1]*ballGreen*shadingFactor, 
						gl_Color[2]*ballBlue*shadingFactor, 1);
	//gl_FragColor = vec4(1, 0, 0, 1);
	//gl_FragColor = gl_Color;
	//gl_FragColor = texture2D(texId,pos);
}
