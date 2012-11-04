// All model vertices and normals are passed to this shader.
// It must transform the vertices as appropriate for the view.
// The view and projection matrices are provided, if you need
// the normal matrix, you must construct it in the shader.

uniform mat4 projMatrix;  //projection matrix
uniform mat4 viewMatrix;  //view matrix (camera)

varying vec3 normal;  //normal that will be interpolated for the fragment shader
varying vec4 vertex;
varying vec3 lightPos;


void main()
{	
	vertex = gl_Vertex;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;  //output the transformed vertex
	lightPos = vec3(0,2,0);
	normal = gl_Normal;
	gl_FrontColor = gl_Color;
	gl_BackColor = gl_Color;
}