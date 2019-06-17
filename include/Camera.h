#ifndef Camera_H
#define Camera_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <cmath>
#include <stdlib.h>
#include <iostream>
#include <matrixArith.h>

/**  @author Alqotel, 16 de Abril 2016,
  *  @class ACC(Alqotel's Camera Class)
  *  Class for camera control
  */

class Camera
{
    public:
        Camera(float CameraPos[3], float CameraFront[3], float CameraUp[3]);
        void setCameraSpeed(GLfloat CameraSpeed);
        void setMouseSpeed(GLfloat MouseSpeed);
        void setApectRatio(GLfloat ApectRatio);
        void setFieldOfView(GLfloat fielOfView);
        void moveCameraDirection(GLfloat xOffSet, GLfloat yOffSet);
        void moveCamera(GLfloat xAxis, GLfloat yAxis, GLfloat zAxis);
        void setPitchLimit(GLfloat PitchLimit);
        void setCameraPosition(GLfloat xAxis, GLfloat yAxis, GLfloat zAxis);
        void setDeltaTime(bool DeltaTimeEnable);
        void zoomInput(GLfloat yAxis);
        void setZoomLimit(GLfloat MinZoom, GLfloat MaxZoom);
        GLfloat getFieldOfView();
        GLfloat getApectRatio();
        float *getCameraMatrix();
        float *getLookAtZero();
        float *getPerspective();
        void setPerspective(GLfloat FOV, GLfloat ASPECT, GLfloat zNear, GLfloat zFar);
        void setPerspective(GLfloat zNear, GLfloat zFar);
        float *cameraPos, *cameraFront, *cameraUp;

    protected:
    private:
        float *lookAt(float *cameraPos, float *lookPos, float *up);
        void processData();
        GLfloat fov = 45.0f;
        GLfloat cameraSpeed = 0.5f, xMovement, yMovement, zMovement;
        GLfloat mouseSensitivity = 0.1f;
        GLfloat aspectRatio;
        float *view;
        float *projection;
        GLfloat xoffset, yoffset;
        GLfloat pitchLimit = 89.0f, pitch, yaw;
        GLfloat deltaTime, currentFrame, lastFrame;
        GLfloat maxZoom = 45.0f, minZoom = 1.0f;
        bool DELTA_TIME;
};

#endif // Camera_H
