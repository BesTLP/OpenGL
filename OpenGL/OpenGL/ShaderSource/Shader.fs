#version 330 core

in vec3 ourColor;  // �Ӷ�����ɫ�����յ���ɫ����

out vec4 FragColor;  // Ƭ����ɫ���������ɫ

void main()
{
    FragColor = vec4(ourColor, 1.0);  // �����յ�����ɫֵת��Ϊ vec4�������� alpha Ϊ 1.0����͸����
};
