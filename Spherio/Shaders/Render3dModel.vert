// All model vertices and normals are passed to this shader.
// It must transform the vertices as appropriate for the view.
// The view and projection matrices are provided, if you need
// the normal matrix, you must construct it in the shader.

uniform mat4 projMatrix;  //projection matrix
uniform mat4 viewMatrix;  //view matrix (camera)

varying vec4 normal;  //normal that will be interpolated for the fragment shader
varying vec4 vertex;
varying vec3 lightPos;


void main()
{	
	vertex = gl_Vertex;
	vertex = gl_ModelViewProjectionMatrix * vertex;  //use the uploaded matrix data
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;  //output the transformed vertex
	lightPos = vec3(0,2, -5);
	vec4 newNorm = vec4(gl_Normal[0], gl_Normal[1], gl_Normal[2], 0);
	normal = normalize(gl_ModelViewProjectionMatrix * newNorm);
	//normal = vec4(gl_Normal[0], gl_Normal[1], gl_Normal[2], 1);
	gl_FrontColor = gl_Color;
	//gl_BackColor = vec4(1, 0, 0, 1);
}