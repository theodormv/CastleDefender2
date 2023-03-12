#include "Matrix3.h"


Vector3f Vec3MulMat3(const Vector3f& vec, const Mat3& mat) {

	Vector3f retVec;
	for (int row = 0; row < 3; row++) {
		for (int col = 0; col < 3; col++) {
			retVec[row] += mat.data[row][col] * vec.get(col);
		}
		
	}
	return retVec;
}

Mat3 getRotationYZ(float rad) {
	Mat3 Mrotx = { 1, 0, 0,
				  0, cos(rad), -sin(rad),
				  0, sin(rad), cos(rad) };

	return Mrotx;
}



Mat3 getRotationXZ(float rad) {
	Mat3 Mroty = { cos(rad), 0, sin(rad),
				   0, 1, 0,
				  -sin(rad), 0, cos(rad) };

	return Mroty;
}


Mat3 getRotationXY(float rad) {
	Mat3 Mroty ={ cos(rad), -sin(rad), 0,
				  sin(rad), cos(rad), 0,
				  0, 0, 1 };
	
	return Mroty;
}

Mat3 getRotationGeneral(Vector3f ax, float rad) {
	Mat3 C = { 0 , -ax[2], ax[1],
				 ax[2], 0, -ax[0],
				 -ax[1], ax[0], 0 };
	Mat3 I = { 1, 0, 0,
			   0, 1, 0,
			   0, 0, 1 };

	Mat3 result = I;

	result = Mat3AddMat3(result, Mat3MulScalar(C, sin(rad)));
	result = Mat3AddMat3(result, Mat3MulScalar(Mat3MulMat3(C, C), 1 - cos(rad)));

	return result;


}

Mat3 Mat3MulMat3(Mat3 mat1, Mat3 mat2) {
	Mat3 result = { 0,0,0,0,0,0,0,0,0 };

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			
			float c = 0;

			for (int k = 0; k < 3; ++k) {
				c += mat1.data[i][k] * mat2.data[k][j];
			}

			result.data[i][j] = c;
		}
	}

	return result;
}

Mat3 Mat3MulScalar(Mat3 mat, float sca) {
	Mat3 result = { 0,0,0,0,0,0,0,0,0 };

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			result.data[i][j] = mat.data[i][j] * sca;
		}
	}
	return result;
}

Mat3 Mat3AddMat3(Mat3 mat1, Mat3 mat2) {
	Mat3 result = { 0,0,0,0,0,0,0,0,0 };

	for (int i = 0; i < 3; ++i) {
		for (int j = 0; j < 3; ++j) {
			result.data[i][j] = mat1.data[i][j] + mat2.data[i][j];
		}
	}

	return result;
}