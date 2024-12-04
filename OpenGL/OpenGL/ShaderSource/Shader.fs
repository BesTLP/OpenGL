#version 330 core

in vec3 ourColor;  // 从顶点着色器接收的颜色数据

out vec4 FragColor;  // 片段着色器的输出颜色

void main()
{
    FragColor = vec4(ourColor, 1.0);  // 将接收到的颜色值转换为 vec4，并设置 alpha 为 1.0（不透明）
};
