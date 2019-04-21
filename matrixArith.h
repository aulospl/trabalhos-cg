#ifndef _MATRIX_ARITH_H_
#define _MATRIX_ARITH_H_

float *createMatrix3(float a11, float a12, float a13, float a21, float a22, float a23, float a31, float a32, float a33);
float *createIdentity3();
float *createDiagonal3(float a11, float a22, float a33);
float *createMatrix4(float a11, float a12, float a13, float a21, float a22, float a23, float a31, float a32, float a33);
float *createIdentity4();
float *createDiagonal4(float a11, float a22, float a33);
float *addMatrix3(float *matrixA, float *matrixB);
float *addMatrix4(float *matrixA, float *matrixB);
float *multScalarMatrix3(float *matrix, int scalar);
float *multScalarMatrix4(float *matrix, int scalar);
float *multMatrix3(float *matrixA, float *matrixB);
float *multMatrix4(float *matrixA, float *matrixB);
float *multVecByMatrix3(float *matrix, float *vec);
float *multVecByMatrix4(float *matrix, float *vec);

#endif
