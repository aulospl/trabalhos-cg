#include "matrixArith.h"

float *addMatrix3(float *matrixA, float *matrixB){
  float *result = new float[9];

  for(int i = 0; i < 9; i++)
    result[i] = matrixA[i] + matrixB[i];

  return result;
}

float *addMatrix4(float *matrixA, float *matrixB){
  float *result = new float[16];

  for(int i = 0; i < 16; i++)
    result[i] = matrixA[i] + matrixB[i];

  return result;
}

float *multScalarMatrix3(float *matrix, int scalar){
  float *result = new float[9];

  for(int i = 0; i < 9; i++)
    result[i] = matrix[i]*scalar;

  return result;
}

float *multScalarMatrix4(float *matrix, int scalar){
  float *result = new float[16];

  for(int i = 0; i < 16; i++)
    result[i] = matrix[i]*scalar;

  return result;
}

float *multMatrix3(float *matrixA, float *matrixB){
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

float *multMatrix4(float *matrixA, float *matrixB){
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

float *multVecByMatrix3(float *matrix, float *vec){
  float *result = new float[3];

  result[0] = matrix[0]*vec[0] + matrix[1]*vec[1] + matrix[2]*vec[2];
  result[1] = matrix[3]*vec[0] + matrix[4]*vec[1] + matrix[5]*vec[2];
  result[2] = matrix[6]*vec[0] + matrix[7]*vec[1] + matrix[8]*vec[2];

  return result;
}

float *multVecByMatrix4(float *matrix, float *vec){
  float *result = new float[4];

  result[0] = matrix[0]*vec[0] + matrix[1]*vec[1] + matrix[2]*vec[2] + matrix[3]*vec[3];
  result[1] = matrix[4]*vec[0] + matrix[5]*vec[1] + matrix[6]*vec[2] + matrix[7]*vec[3];
  result[2] = matrix[8]*vec[0] + matrix[9]*vec[1] + matrix[10]*vec[2] + matrix[11]*vec[3];
  result[3] = matrix[12]*vec[0] + matrix[13]*vec[1] + matrix[14]*vec[2] + matrix[15]*vec[3];

  return result;
}
