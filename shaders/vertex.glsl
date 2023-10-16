#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 aTexCoord;

out vec3 ourColor;
out vec2 TexCoord; 

uniform mat4 transform;

uniform int num;

void main()
{
    if(num == 0)
    {
	    gl_Position = transform * vec4(aPos, 1.0f);
    }
    else if(num == 1)
    {
        gl_Position = vec4(aPos, 1.0f);
    }
	ourColor = vec3(1.0f, 0.0f, 0.0f);
    TexCoord = vec2(aTexCoord.x, aTexCoord.y);
}
