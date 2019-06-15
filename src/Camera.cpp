#include "Camera.h"

Camera::Camera(float CameraPos[3], float CameraFront[3], float CameraUp[3]){
    cameraUp = new float[3];
    cameraFront = new float[3];
    cameraPos = new float[3];
    cameraUp[0] = CameraUp[0];
    cameraUp[1] = CameraUp[1];
    cameraUp[2] = CameraUp[2];
    cameraPos[0] = CameraPos[0];
    cameraPos[1] = CameraPos[1];
    cameraPos[2] = CameraPos[2];
    cameraFront[0] = CameraFront[0];
    cameraFront[1] = CameraFront[1];
    cameraFront[2] = CameraFront[2];
    float *lookPos = addVec3(cameraPos, cameraFront);
    view = lookAt(cameraPos, lookPos, cameraUp);
    free (lookPos);
    DELTA_TIME = true;
}

void Camera::setCameraSpeed(GLfloat CameraSpeed){
    cameraSpeed = CameraSpeed;
}

void Camera::setMouseSpeed(GLfloat MouseSpeed){
    mouseSensitivity = MouseSpeed;
}

void Camera::setApectRatio(GLfloat AspectRatio){
    aspectRatio = AspectRatio;
}

void Camera::setFieldOfView(GLfloat fieldOfView){
    fov = fieldOfView;
}

void Camera::moveCameraDirection(GLfloat xOffSet, GLfloat yOffSet){

    xoffset = xOffSet;
    yoffset = yOffSet;
}

void Camera::moveCamera(GLfloat xAxis, GLfloat yAxis, GLfloat zAxis){
    xMovement = xAxis;
    yMovement = yAxis;
    zMovement = zAxis;
}

void Camera::setPitchLimit(GLfloat PitchLimit){
    pitchLimit = PitchLimit;
}

void Camera::setCameraPosition(GLfloat xAxis, GLfloat yAxis, GLfloat zAxis){
    cameraPos[0] = xAxis;
    cameraPos[1] = yAxis;
    cameraPos[2] = zAxis;
}

void Camera::setDeltaTime(bool DeltaTimeEnable){
    DELTA_TIME = DeltaTimeEnable;
}

void Camera::zoomInput(GLfloat yAxis){
    fov -= yAxis;
    if(fov < minZoom){
        fov = minZoom;
    }
    if(fov > maxZoom){
        fov = maxZoom;
    }
}

void Camera::setZoomLimit(GLfloat MinZoom, GLfloat MaxZoom){
    if(MaxZoom <= 180.0f){
        maxZoom = MaxZoom;
    }
    if(MinZoom >= 1.0f){
        minZoom = MinZoom;
    }
}

GLfloat Camera::getFieldOfView(){
    return glm::radians(fov);
}

GLfloat Camera::getApectRatio(){
    return aspectRatio;
}

float *Camera::getCameraMatrix(){
    processData();
    free(view);
    float *lookPos = addVec3(cameraPos, cameraFront);
    view = lookAt(cameraPos, lookPos, cameraUp);
    free (lookPos);
    return view;
}

float *Camera::getLookAtZero(){
    float auxZero[3] = {0.0,0.0,0.0};
    return lookAt(auxZero, auxZero, auxZero);
}

float* Camera::lookAt(float *cameraPos, float *lookPos, float *up){
    float Z[3];
    Z[0] = lookPos[0] - cameraPos[0];
    Z[1] = lookPos[1] - cameraPos[1];
    Z[2] = lookPos[2] - cameraPos[2];
    float *X = crossVec3(up, Z);
    normalizeVec3(X);
    float *Y = crossVec3(Z, X);
    normalizeVec3(Y);
    // normalizeVec3(Z);
    float *ret = createMatrix4(X[0], Y[0], Z[0], -cameraPos[0],
                            X[1], Y[1], Z[1], -cameraPos[1],
                            X[2], Y[2], Z[2], -cameraPos[2],
                            0,    0,    0,    0);
    free(X);
    free(Y);    
    return ret;
}

glm::mat4 Camera::getPerspective(){
    return projection;
}

void Camera::processData(){

////**************MOUSE MOVEMENT********************////

////*****DELTA TIME******////
    if(DELTA_TIME){
        currentFrame = glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;
        deltaTime *= 10.0f;
    }else{
        deltaTime = 1.0f;
    }
////****END DELTA TIME***////

    pitch += yoffset * mouseSensitivity;
    yaw   += xoffset * mouseSensitivity;
    xoffset = 0.0f;
    yoffset = 0.0f;
    if(pitch > 89.0f){
        pitch = 89.0f;
    }
    if(pitch < -89.0f){
        pitch = -89.0f;
    }
    // glm::vec3 front;
    cameraFront[0] = cos((pitch*M_PI)/180.0) * cos((yaw*M_PI)/180.0) * deltaTime;
    cameraFront[1] = sin((pitch*M_PI)/180.0) * deltaTime;
    cameraFront[2] = cos((pitch*M_PI)/180.0) * sin((yaw*M_PI)/180.0) * deltaTime;
    normalizeVec3(cameraFront);
////***************END MOUSE MOVEMENT**************////

////***************CAMERA MOVEMENT*****************////
    float *oldCamera = cameraPos;
    float *walked = scalarVec3(cameraFront, zMovement * cameraSpeed * deltaTime);
    cameraPos = addVec3(cameraPos, walked);
    free(oldCamera);
    free(walked);
    oldCamera = cameraPos;
    float *right = crossVec3(cameraFront, cameraUp);
    normalizeVec3(right);
    walked = scalarVec3(right, xMovement * cameraSpeed * deltaTime);
    cameraPos =  addVec3(cameraPos, walked);
    free(oldCamera);
    free(walked);
    free(right);
    
////*************END CAMERA MOVEMENT***************////

}

void Camera::setPerspective(GLfloat FOV, GLfloat ASPECT, GLfloat zNear, GLfloat zFar){
    if(!FOV){
        FOV = fov;
    }
    if(!ASPECT){
        ASPECT = aspectRatio;
    }
    projection = glm::perspective(glm::radians(FOV), ASPECT, zNear, zFar);
}

void Camera::setPerspective(GLfloat zNear, GLfloat zFar){
    projection = glm::perspective(glm::radians(fov), aspectRatio, zNear, zFar);
}


//glm::mat4 Camera::getCamera(GLfloat deltaTime){
//    return view;
//}
