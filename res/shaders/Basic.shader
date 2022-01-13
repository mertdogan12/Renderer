#shader vertex
#version 330 core
  
layout(location = 1) in vec2 position;
layout(location = 2) in vec2 texCord;

out vec2 v_TexCoords;

uniform mat4 u_MVP;
 
void main()
{
    gl_Position = u_MVP * vec4(position, 1.0, 1.0);
    v_TexCoords = texCord;
};


#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

in vec2 v_TexCoords;

uniform sampler2D u_Texture;
                               
void main()
{
    vec4 texColor = texture(u_Texture, v_TexCoords);
    color = texColor;
};
