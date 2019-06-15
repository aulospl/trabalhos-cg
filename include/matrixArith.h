#ifndef _MATRIX_ARITH_H_
#define _MATRIX_ARITH_H_

float *createMatrix3(float a11, float a12, float a13, float a21, float a22, float a23, float a31, float a32, float a33);
float *createIdentity3();
float *createDiagonal3(float a11, float a22, float a33);
float *createMatrix4(float a11, float a12, float a13, float a14, float a21, float a22, float a23, float a24, float a31, float a32, float a33, float a34, float a41, float a42, float a43, float a44);
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
float *crossVec3(float *vecA, float *vecB);
float *crossVec4(float *vecA, float *vecB);
void normalizeVec3(float *vec);
void normalizeVec4(float *vec);
float *addVec3(float *vecA, float *vecB);
float *addVec4(float *vecA, float *vecB);
float dotVec3(float *vecA, float *vecB);
float dotVec4(float *vecA, float *vecB);
float *scalarVec3(float *vec, float scalar);
float *scalarVec4(float *vec, float scalar);

#endif
