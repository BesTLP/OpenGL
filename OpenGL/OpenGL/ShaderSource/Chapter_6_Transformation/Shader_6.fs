#version 330 core

in vec3 ourColor;  // �Ӷ�����ɫ�����յ���ɫ����
in vec2 TexCoord;
uniform sampler2D texture1;
uniform sampler2D texture2;
uniform float mixValue;
out vec4 FragColor;  // Ƭ����ɫ���������ɫ
void main()
{
     FragColor = mix(texture(texture1, TexCoord), texture(texture2, TexCoord), mixValue);
};