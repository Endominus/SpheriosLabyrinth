// All model vertices and normals are passed to this shader.
// It must transform the vertices as appropriate for the view.
// The view and projection matrices are provided, if you need
// the normal matrix, you must construct it in the shader.

uniform vec3 ballPos;
uniform float elapsedTime;  //time in seconds since simulation began
uniform sampler2D texId; //this is the texture unit that has the rendered image
attribute float colorIndex;


varying vec3 normal;  //normal that will be interpolated for the fragment shader
varying vec4 vertex;
varying vec3 lightPos;
varying float index;


void main()
{	
	index = colorIndex;
	vertex = gl_Vertex;
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;  //output the transformed vertex
	lightPos = ballPos;
	normal = gl_Normal;
	gl_FrontColor = gl_Color;
	gl_BackColor = gl_Color;
}