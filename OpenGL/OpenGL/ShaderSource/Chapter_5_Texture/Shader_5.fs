#version 330 core

in vec3 ourColor;  // 从顶点着色器接收的颜色数据
in vec2 TexCoord;
uniform sampler2D texture1;
uniform sampler2D texture2;
out vec4 FragColor;  // 片段着色器的输出颜色
void main()
{
     FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), 0.2);
};
