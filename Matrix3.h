#pragma once
#include "VectorNd.h"

struct Mat3 {
	float data[3][3];
};

Vector3f Vec3MulMat3(const Vector3f& vec, const Mat3& mat);


Mat3 getRotationYZ (float rad);
Mat3 getRotationXZ (float rad);
Mat3 getRotationXY (float rad);
Mat3 getRotationGeneral(Vector3f ax, float rad);

Mat3 Mat3MulMat3(Mat3 mat1, Mat3 mat2);
Mat3 Mat3MulScalar(Mat3 mat, float sca);
Mat3 Mat3AddMat3(Mat3 mat1, Mat3 mat2);