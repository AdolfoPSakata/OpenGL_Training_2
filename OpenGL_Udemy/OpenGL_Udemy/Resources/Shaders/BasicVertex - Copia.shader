#shader vertex
#version 450 core
        
layout(location = 0) in vec4 position;
//layout(location = 1) in vec4 u_Color;
//layout(location = 2) in vec2 u_TexCoord;
//layout(location = 3) in float u_TexIndex;

//uniform mat4 u_MVP;

//out vec4 v_Color;
//out vec2 v_TextCoord;
//out float v_TexIndex;

void main()
{
    //v_TexIndex = u_TexIndex;
    //v_Color = u_Color;
   // v_TextCoord = u_TexCoord;
    //gl_Position = u_MVP * position;
   gl_Position =  position;
};