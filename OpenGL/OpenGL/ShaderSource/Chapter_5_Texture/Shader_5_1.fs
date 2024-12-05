#version 330 core

in vec3 ourColor;  // �Ӷ�����ɫ�����յ���ɫ����
in vec2 TexCoord;
uniform sampler2D texture1;
uniform sampler2D texture2;
out vec4 FragColor;  // Ƭ����ɫ���������ɫ
void main()
{
     FragColor = mix(texture(texture1, TexCoord), texture(texture2, vec2(1 - TexCoord.x, TexCoord.y)), 0.2);
};
