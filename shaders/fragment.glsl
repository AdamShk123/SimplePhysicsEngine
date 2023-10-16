#version 330 core
out vec4 FragColor;

in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D texture1;
uniform sampler2D texture2;

uniform int num;

void main()
{
    if(num == 0)
    {
	    FragColor = texture(texture1, TexCoord);
    }
    else if(num == 1)
    {
	    FragColor = texture(texture2, TexCoord);
    }
}
