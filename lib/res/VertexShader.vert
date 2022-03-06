#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec3 aColor; // the color variable has attribute position 1
layout (location = 2) in vec2 aTex;

uniform vec3 inputColour;

out vec3 ourColor; // output a color to the fragment shader
out vec2 texCoord;

uniform float scale;

uniform mat4 model;
uniform mat4 view;
uniform mat4 proj;

uniform mat4 camMatrix;

void main()
{
    gl_Position = proj * view * model * vec4(aPos, 1.0);
    //gl_Position = camMatrix * vec4(aPos, 1.0);
    ourColor = aColor; // set ourColor to the input color we got from the vertex data
    //ourColor = inputColour;
    texCoord = aTex;
}  
