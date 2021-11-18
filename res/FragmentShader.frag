#version 330 core
out vec4 FragColor;  
in vec3 ourColor;
in vec2 texCoord;

uniform sampler2D tex0;
  
void main()
{
    //FragColor = vec4(ourColor, 1.0);
    FragColor = texture(tex0, texCoord);
}