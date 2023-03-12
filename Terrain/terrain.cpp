#include "terrain.h"
#include "../Game.h"

TextureCube* Terrain::tex = nullptr;
Terrain::Terrain(float w, float h, float d, Vector3f pos) :shape(new Box( w, h, d, pos)) {


	const std::vector<Vector3f>& points = shape->getPoints();
	std::vector<uint32>& inds = shape->getInstructions();


	uint16 vertNum = points.size() * 3;

	Vertex* tempVerts = new Vertex[points.size()];


	tempVerts[0].textureCorrd[0] = 0.f; tempVerts[0].textureCorrd[1] = 0.f; //front bottom left
	tempVerts[1].textureCorrd[0] = 0.f; tempVerts[1].textureCorrd[1] = 1.f; //front bottom right
	tempVerts[2].textureCorrd[0] = 1.f; tempVerts[2].textureCorrd[1] = 0.f; //front top left
	tempVerts[3].textureCorrd[0] = 1.f; tempVerts[3].textureCorrd[1] = 1.f; //front top right
	tempVerts[4].textureCorrd[0] = 0.f; tempVerts[4].textureCorrd[1] = 0.f; //back bottom left
	tempVerts[5].textureCorrd[0] = 0.f; tempVerts[5].textureCorrd[1] = 1.f; //back bottom right
	tempVerts[6].textureCorrd[0] = 1.f; tempVerts[6].textureCorrd[1] = 0.f; //back top left
	tempVerts[7].textureCorrd[0] = 1.f; tempVerts[7].textureCorrd[1] = 1.f; //back top right
	

	for (int i = 0; i < points.size(); ++i) {

		int pointNum = i % 8;

		for (int j = 0; j < 3; ++j) {
			tempVerts[i].position[j] = points[i].get(j);
			tempVerts[i].normal[j] = 0;
			//tempVerts[i].color[j] = 1.f;
		}

	
	}

	model = new Model(tempVerts, points.size(), &*inds.begin(), inds.size(), tex);

}


Terrain::Terrain(const Terrain& other) : shape(new BoxCore(*(BoxCore*)other.shape)), model(new Model(*other.model)){}


Terrain::~Terrain() {
	delete shape;
	delete model;
}


void Terrain::draw() const {


	Game::activeCamera->Draw(*model, reinterpret_cast<BoxCore*>(shape)->getCenter(), 0, 0, 0);


}