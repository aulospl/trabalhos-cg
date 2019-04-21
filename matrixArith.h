#ifndef _MATRIX_ARITH_H_
#define _MATRIX_ARITH_H_

float *addMatrix3(float *matrixA, float *matrixB);
float *addMatrix4(float *matrixA, float *matrixB);
float *multScalarMatrix3(float *matrix, int scalar);
float *multScalarMatrix4(float *matrix, int scalar);
float *multMatrix3(float *matrixA, float *matrixB);
float *multMatrix4(float *matrixA, float *matrixB);
float *multVecByMatrix3(float *matrix, float *vec);
float *multVecByMatrix4(float *matrix, float *vec);

#endif
