#shader vertex
#version 460 core

layout(location = 0) in vec4 vertex_position;
//layout(location = 1) in vec3 vertex_colour;
layout(location = 1) in vec3 vertex_normal;
layout(location = 2) in vec2 vertex_texture;

//out vec3 vertex_color;
out vec3 Normal;
out vec4 fragPos;
out vec3 texDir;


uniform vec3 modelRotation;
uniform vec3 modelPosition;

uniform mat4 lookAtMat;
uniform mat4 projection;

uniform vec3 boxDims;


//uniform vec3 modelAxisPitch;
//uniform vec3 modelAxisYaw;
//uniform vec3 modelAxisRoll;

vec3 rotateVecAroundVecAx(in vec3 vec, in vec3 vecAx, in float theta) {

	vec3 ap = (dot(vec, vecAx) / dot(vecAx, vecAx)) * vecAx;
	vec3 ao = vec - ap;

	vec3 orth = cross(vecAx, ao);

	float x1 = cos(theta) / (length(ao));
	float x2 = sin(theta) / (length(orth));


	vec3 aor = length(ao) * (x1 * ao + x2 * orth);

	vec3 a = ap + aor;

	if (length(ao) == 0) {
		a = vec;
	}

	return a;
}

void setMatrixRotationX(in float rotation, out mat3 rotationMat) {
	rotationMat[0] = vec3(1, 0, 0);
	rotationMat[1] = vec3(0, cos(rotation), sin(rotation));
	rotationMat[2] = vec3(0, -sin(rotation), cos(rotation));
}

void setMatrixRotationY(in float rotation, out mat3 rotationMat) {
	rotationMat[0] = vec3(cos(rotation), 0, -sin(rotation));
	rotationMat[1] = vec3(0, 1, 0);
	rotationMat[2] = vec3(sin(rotation), 0, cos(rotation));
}

void setMatrixRotationZ(in float rotation, out mat3 rotationMat) {
	rotationMat[0] = vec3(cos(rotation), -sin(rotation), 0);
	rotationMat[1] = vec3(sin(rotation), cos(rotation), 0);
	rotationMat[2] = vec3(0, 0, 1);
}

mat3 getRotationMatrix(in float rotx, in float roty, in float rotz) {
	mat3 tempRot;
	mat3 retMat;
	setMatrixRotationX(rotx, tempRot);
	retMat = tempRot;
	setMatrixRotationY(roty, tempRot);
	retMat *= tempRot;
	setMatrixRotationZ(rotz, tempRot);
	retMat *= tempRot;

	return retMat;
}

mat3 getRotationMatrix(in vec3 rot) {
	mat3 tempRot;
	mat3 retMat;
	setMatrixRotationX(rot.x, tempRot);
	retMat = tempRot;
	setMatrixRotationY(rot.y, tempRot);
	retMat *= tempRot;
	setMatrixRotationZ(rot.z, tempRot);
	retMat *= tempRot;

	return retMat;
}


void main() {


	//rotation code x y z plane

	vec4 verts = vec4((vertex_position.xyz * getRotationMatrix(modelRotation)) + modelPosition, 1.f);


	gl_Position = projection * (lookAtMat * verts);


	//	vertex_color = vertex_colour;

	texDir.x = verts.x / boxDims.x;
	texDir.y = verts.y / boxDims.y;
	texDir.z = verts.z / boxDims.z;

	//used for lighting
	Normal = vertex_normal * getRotationMatrix(modelRotation); //* rotationModel;
	//Normal = (vec4(Normal, 1.f)).xyz;
	fragPos = lookAtMat * verts;
}

#shader fragment
#version 460 core

//in vec3 vertex_color;
in vec3 Normal;
in vec4 fragPos;
in vec3 texDir;

out vec4 out_colour;

uniform vec3 lightPos;
uniform vec3 lightColour;

uniform samplerCube samp;

void main() {

	vec3 final = texture(samp, texDir).xyz;

	//ambient light
	float ambientStrength = .2f;

	final *= ambientStrength;

	//diffuse light
	vec3 lightDir = normalize(lightPos - fragPos.xyz);
	float diffuseStrength = max(dot(lightDir, Normal), 0.f);


	final += diffuseStrength * lightColour;

	out_colour = vec4(final, 1);
	//out_colour += vec4(vertex_color, 1.f);
}