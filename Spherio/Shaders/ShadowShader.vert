// All model vertices and normals are passed to this shader.
// It must transform the vertices as appropriate for the view.
// The view and projection matrices are provided, if you need
// the normal matrix, you must construct it in the shader.



void main()
{	
	gl_Position = gl_ModelViewProjectionMatrix * gl_Vertex;  //output the transformed vertex
	gl_FrontColor = gl_Color;
	gl_BackColor = gl_Color;
}