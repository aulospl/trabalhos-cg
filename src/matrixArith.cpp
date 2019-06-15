#include "matrixArith.h"
#include <cmath>

float *createMatrix3(float a11, float a12, float a13,//cria uma matriz 3x3 com os valores passados
                     float a21, float a22, float a23,
                     float a31, float a32, float a33){

    float *result = new float[9];
    result[0] = a11;
    result[1] = a12;
    result[2] = a13;
    result[3] = a21;
    result[4] = a22;
    result[5] = a23;
    result[6] = a31;
    result[7] = a32;
    result[8] = a33;
    return result;
}


float *createIdentity3(){//cria a matriz identidade 3x3
    return createMatrix3( 1,  0,  0, 0, 1, 0, 0, 0, 1);
}
float *createDiagonal3(float a11, float a22, float a33){//cria uma matriz 3x3 apenas com valores na diagonal principal
    return createMatrix3( a11,  0,  0, 0, a22, 0, 0, 0, a33);
}

float *createMatrix4(float a11, float a12, float a13, float a14,//cria uma matriz 4x4 com os valores passados
                     float a21, float a22, float a23, float a24,
                     float a31, float a32, float a33, float a34,
                     float a41, float a42, float a43, float a44){

    float *result = new float[16];
    result[0] = a11;
    result[1] = a12;
    result[2] = a13;
    result[3] = a14;
    result[4] = a21;
    result[5] = a22;
    result[6] = a23;
    result[7] = a24;
    result[8] = a31;
    result[9] = a32;
    result[10] = a33;
    result[11] = a34;
    result[12] = a41;
    result[13] = a42;
    result[14] = a43;
    result[15] = a44;
    return result;
}


float *createIdentity4(){//cria a matriz identidade 4x4
    return createMatrix4(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1);
}
float *createDiagonal4(float a11, float a22, float a33, float a44){//cria uma matriz 4x4 apenas com valores na diagonal principal
    return createMatrix4(a11, 0, 0, 0, 0, a22, 0, 0, 0, 0, a33, 0, 0, 0, 0, a44);
}

float *addMatrix3(float *matrixA, float *matrixB){//adiciona as matrizes passadas: A + B, caso 3x3
  float *result = new float[9];

  for(int i = 0; i < 9; i++)
    result[i] = matrixA[i] + matrixB[i];

  return result;
}

float *addMatrix4(float *matrixA, float *matrixB){//adiciona as matrizes passadas: A + B, caso 4x4
  float *result = new float[16];

  for(int i = 0; i < 16; i++)
    result[i] = matrixA[i] + matrixB[i];

  return result;
}

float *multScalarMatrix3(float *matrix, int scalar){//multiplica a matriz passada por um escalar, caso 3x3
  float *result = new float[9];

  for(int i = 0; i < 9; i++)
    result[i] = matrix[i]*scalar;

  return result;
}

float *multScalarMatrix4(float *matrix, int scalar){//multiplica a matriz passada por um escalar, caso 4x4
  float *result = new float[16];

  for(int i = 0; i < 16; i++)
    result[i] = matrix[i]*scalar;

  return result;
}

float *multMatrix3(float *matrixA, float *matrixB){//multiplica as matrizes uma pela outra, na ordem que foram passadas: matrizA * matrizB, caso 3x3
  float *result = new float[9];
  int line = 0;

  for(int i = 0; i < 9; i++){
    if(i % 3 == 0){
      line++;
    }
    if(line == 1){
      result[i] = matrixA[0]*matrixB[(i%3)] + matrixA[1]*matrixB[(i%3) + 3] + matrixA[2]*matrixB[(i%3) + 6];
    } else if (line == 2){
      result[i] = matrixA[3]*matrixB[(i%3)] + matrixA[4]*matrixB[(i%3) + 3] + matrixA[5]*matrixB[(i%3) + 6];
    } else {
      result[i] = matrixA[6]*matrixB[(i%3)] + matrixA[7]*matrixB[(i%3) + 3] + matrixA[8]*matrixB[(i%3) + 6];
    }
  }

  return result;
}

float *multMatrix4(float *matrixA, float *matrixB){//multiplica as matrizes uma pela outra, na ordem que foram passadas: matrizA * matrizB, caso 4x4
  float *result = new float[16];
  int line = 0;

  for(int i = 0; i < 16; i++){
    if(i % 4 == 0){
      line++;
    }
    if(line == 1){
      result[i] = matrixA[0]*matrixB[(i%4)] + matrixA[1]*matrixB[(i%4) + 4] + matrixA[2]*matrixB[(i%4) + 8] + matrixA[3]*matrixB[(i%4) + 12];
    } else if (line == 2){
      result[i] = matrixA[4]*matrixB[(i%4)] + matrixA[5]*matrixB[(i%4) + 4] + matrixA[6]*matrixB[(i%4) + 8] + matrixA[7]*matrixB[(i%4) + 12];
    } else if (line == 3){
      result[i] = matrixA[8]*matrixB[(i%4)] + matrixA[9]*matrixB[(i%4) + 4] + matrixA[10]*matrixB[(i%4) + 8] + matrixA[11]*matrixB[(i%4) + 12];
    } else {
      result[i] = matrixA[12]*matrixB[(i%4)] + matrixA[13]*matrixB[(i%4) + 4] + matrixA[14]*matrixB[(i%4) + 8] + matrixA[15]*matrixB[(i%4) + 12];
    }
  }

  return result;
}

float *multVecByMatrix3(float *matrix, float *vec){//multiplica o vetor pela matriz 3x3: matriz*vetor
  float *result = new float[3];

  result[0] = matrix[0]*vec[0] + matrix[1]*vec[1] + matrix[2]*vec[2];
  result[1] = matrix[3]*vec[0] + matrix[4]*vec[1] + matrix[5]*vec[2];
  result[2] = matrix[6]*vec[0] + matrix[7]*vec[1] + matrix[8]*vec[2];

  return result;
}

float *multVecByMatrix4(float *matrix, float *vec){//multiplica o vetor pela matriz 4x4: matriz*vetor
  float *result = new float[4];

  result[0] = matrix[0]*vec[0] + matrix[1]*vec[1] + matrix[2]*vec[2] + matrix[3]*vec[3];
  result[1] = matrix[4]*vec[0] + matrix[5]*vec[1] + matrix[6]*vec[2] + matrix[7]*vec[3];
  result[2] = matrix[8]*vec[0] + matrix[9]*vec[1] + matrix[10]*vec[2] + matrix[11]*vec[3];
  result[3] = matrix[12]*vec[0] + matrix[13]*vec[1] + matrix[14]*vec[2] + matrix[15]*vec[3];

  return result;
}


float *crossVec3(float *vecA, float *vecB){
  float *result = new float[3];

  result[0] = vecA[1] * vecB[2] - vecA[2] * vecB[1];
  result[1] = vecA[0] * vecB[2] - vecA[2] * vecB[0];
  result[2] = vecA[0] * vecB[1] - vecA[1] * vecB[0];

  return result;
}

void normalizeVec3(float *vec){
  float norm = sqrt(pow(vec[0],2) + pow(vec[1],2) + pow(vec[2],2));
  vec[0] /= norm;
  vec[1] /= norm;
  vec[2] /= norm;
}

float *addVec3(float *vecA, float *vecB){
  float *result = new float[3];

  result[0] = vecA[0] + vecB[0];
  result[1] = vecA[1] + vecB[1];
  result[2] = vecA[2] + vecB[2];

  return result;
}

float dotVec3(float *vecA, float *vecB){
  return vecA[0]*vecB[0] + vecA[1]*vecB[1] + vecA[2]*vecB[2];  
}

float *scalarVec3(float *vec, float scalar){
  float *result = new float[3];

  result[0] = vec[0]*scalar;
  result[1] = vec[1]*scalar;
  result[2] = vec[2]*scalar;

  return result;
}
