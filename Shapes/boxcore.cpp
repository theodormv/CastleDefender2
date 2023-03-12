#include "boxcore.h"

BoxCore::BoxCore(float w, float h, float d) : width(w), height(h)
, depth(d), center(nullptr) {


	const float hw = w / 2.f;
	const float hh = h / 2.f;
	const float hd = d / 2.f; 

	points = { {  hw,  hh, -hd},    //front bottom left
			   { -hw,  hh, -hd},    //front bottom right
			   {  hw, -hh, -hd},    //front top left
			   { -hw, -hh, -hd},    //front top right
			   {  hw,  hh,  hd},    //back bottom left
			   { -hw,  hh,  hd},	//back bottom right
			   {  hw, -hh,  hd},	//back top left
			   { -hw, -hh,  hd} };	//back top right

	inds = { 
		//front face
		0, 2, 3,
		0, 3, 1,
		//back face
		5, 6, 4,
		5, 7, 6,
		//left face
		1, 7, 5,
		1, 3, 7,
		//right face
		4, 6, 2,
		4, 2, 0,
		//top face
		1, 5, 4,
		1, 4, 0,
		//bottom face
		2, 6, 7,
		2, 7, 3
		
	
	};

}

BoxCore::BoxCore(const BoxCore& other) : width(other.width), height(other.height), depth(other.depth), center(new Vector3f(*other.center)) {}


bool BoxCore::checkIntersect(BoxCore* other) {

	const Vector3f checkPoint = *center - *other->center;

	float tHeight = height / 2.f + other->height / 2.f;
	float tWidth = width / 2.f + other->width / 2.f;
	float tDepth = depth / 2.f + other->depth / 2.f;

	if (!(checkPoint.get(0) > -tWidth && checkPoint.get(0) > tWidth)) return false;

	if (!(checkPoint.get(1) > -tHeight && checkPoint.get(1) > tHeight)) return false;

	if (!(checkPoint.get(2) > -tDepth && checkPoint.get(2) > tDepth)) return false;

	return true;
}


Vector3f BoxCore::correctedIntersect(BoxCore* other) {

	const Vector3f checkPoint = *center - *other->center;

	Vector3f opVec;
	Vector3f retVec;

	float tWidth = width / 2.f + other->width / 2.f;
	float tHeight = height / 2.f + other->height / 2.f;
	float tDepth = depth / 2.f + other->depth / 2.f;

	float x = checkPoint.get(0);
	float y = checkPoint.get(1);
	float z = checkPoint.get(2);

	//std::cout << "BoxCore::CorrectedIntersect : " << checkPoint << tWidth << " " << tHeight << " " << tDepth << std::endl;


	if (x > -tWidth && x < tWidth) {
		opVec.set(0, (tWidth - abs(x))*(x/(abs(x))));
		if (y > -tHeight && y < tHeight) {
			opVec.set(1, (tHeight - abs(y)) * (y / (abs(y))));
			if (z > -tDepth && z < tDepth) {
				opVec.set(2, (tDepth - abs(z)) * (z / (abs(z))));

				float min = abs(opVec.get(0));
				int minind = 0;
				for (int i = 1; i < 3; ++i) {
					if (abs(opVec.get(i)) < min) {
						min = abs(opVec.get(i));
						minind = i;
					}
				}

				retVec.set(minind, -opVec[minind]);
			}
		}
	}
	return retVec;
}

bool BoxCore::checkPoint(const Vector3f& point) {

	const Vector3f checkPoint = point - *center;

	if (!(checkPoint.get(0) > -width && checkPoint.get(0) > width)) return false;

	if (!(checkPoint.get(1) > -height && checkPoint.get(1) > height)) return false;

	if (!(checkPoint.get(2) > -depth && checkPoint.get(2) > depth)) return false;

	return true;
}
