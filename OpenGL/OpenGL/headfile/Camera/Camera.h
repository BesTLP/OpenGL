#ifndef CAMERA_H
#define CAMERA_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement 
{
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

const float YAW = -90.0f;
const float PITCH = 0.0f;
const float SPEED = 2.5f;
const float SENSITIVITY = 0.1f;
const float ZOOM = 45.0f;

class Camera 
{
public:
    // Camera Attributes
    // 用于定义LookAt矩阵
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;

    glm::vec3 WorldUp;
    // Euler Angles
    float Yaw;
    float Pitch;

    float MovementSpeed;
    
    float MouseSensivity;
    
    // fov
    float Zoom;

    Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f),
        glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
        float yaw = YAW,
        float pitch = PITCH) :
        Front(glm::vec3(0.0f, 0.0f, -1.0f)),
        MovementSpeed(SPEED),
        MouseSensivity(SENSITIVITY),
        Zoom(ZOOM)
    {
        Position = position;
        WorldUp = up;
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    Camera(float posX, float posY, float posZ,
        float upX, float upY, float upZ,
        float yaw, float pitch) :
        Front(glm::vec3(0.0f, 0.0f, -1.0f)),
        MovementSpeed(SPEED),
        MouseSensivity(SENSITIVITY),
        Zoom(ZOOM)
    {
        Position = glm::vec3(posX, posY, posZ);
        WorldUp = glm::vec3(upX, upY, upZ);
        Yaw = yaw;
        Pitch = pitch;
        updateCameraVectors();
    }

    glm::mat4 getViewMatrix() 
    {
        //glm::mat4 transform = glm::mat4(1.0f);
        //transform[3][0] = -Position.x;
        //transform[3][1] = -Position.y;
        //transform[3][2] = -Position.z;

        //glm::mat4 rotation = glm::mat4(1.0f);
        //rotation[0][0] = Right.x;
        //rotation[1][0] = Right.y;
        //rotation[2][0] = Right.z;
        //rotation[0][1] = Up.x;
        //rotation[1][1] = Up.y;
        //rotation[2][1] = Up.z;
        //rotation[0][2] = -Front.x;
        //rotation[1][2] = -Front.y;
        //rotation[2][2] = -Front.z;

        //return rotation * transform;
        return glm::lookAt(Position, Position + Front, Up);
    }

    void ProcessKeyboard(Camera_Movement direction, float deltaTime)
    {
        float velocity = deltaTime * MovementSpeed;
        if (direction == FORWARD)
        {
            Position += Front * velocity;
        }
        if (direction == BACKWARD)
        {
            Position -= Front * velocity;
        }
        if (direction == RIGHT)
        {
            Position += Right * velocity;
        }
        if (direction == LEFT)
        {
            Position -= Right * velocity;
        }
        //Position.y = 0; // Create FPS Camera, you cannot fly.
    }

    void ProcessMouseMovement(float xOffset, float yOffset, GLboolean constrainPitch = true)
    {
        xOffset *= MouseSensivity;
        yOffset *= MouseSensivity;

        Pitch += yOffset;
        Yaw += xOffset;

        if (constrainPitch)
        {
            if (Pitch > 89.0f)
                Pitch = 89.0f;
            if (Pitch < -89.0f)
                Pitch = -89.0f;
        }
        updateCameraVectors();
    }

    void ProcessMouseScroll(float yOffset)
    {
        Zoom -= (float)yOffset;
        if (Zoom < 1.0f) Zoom = 1.0f;
        if (Zoom > 45.0f) Zoom = 45.0f;
    }

private:

    // 用于更新摄像机方向坐标系
    void updateCameraVectors() 
    {
        glm::vec3 front;
        front.x = cos(glm::radians(Pitch)) * cos(glm::radians(Yaw));
        front.y = sin(glm::radians(Pitch));
        front.z = cos(glm::radians(Pitch)) * sin(glm::radians(Yaw));

        Front = glm::normalize(front);
        Right = glm::normalize(glm::cross(Front, WorldUp));
        Up = glm::normalize(glm::cross(Right, Front));
    }
};

#endif // !CAMERA_H
