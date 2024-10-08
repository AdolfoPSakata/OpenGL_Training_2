#shader fragment
#version 450 core

layout(location = 0) out vec4 color;

//in vec2 v_TexCoord;
//in float v_TexIndex;
//in vec4 v_position;

//uniform sampler2D u_Textures[2];
uniform vec4 u_Color;

void main()
{
    //int index = int(v_TexIndex);
    //vec4 texColor = texture(u_Textures[index], v_TexCoord);
    color = u_Color;
};