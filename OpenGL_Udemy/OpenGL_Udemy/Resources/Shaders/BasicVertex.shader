#shader vertex
#version 450 core
        
layout(location = 0) in vec4 position;
layout(location = 1) in vec4 color;
layout(location = 2) in vec2 texCoord;

uniform mat4 u_MVP;

out vec4 v_Color;
out vec2 v_TextCoord;
out vec2 v_TexCoord;

void main()
{
    gl_Position = u_MVP * position;
    v_Color = color;
    v_TexCoord = texCoord;
};