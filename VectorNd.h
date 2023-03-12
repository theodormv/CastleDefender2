#pragma once
#include <memory>
#include <iostream>
#include <cmath>
#include <cstring>
#include <cassert>
#include <type_traits>

#define USE
#ifdef USE


#define PI 3.14159265359
//#define ASSERT(x) if(!(x)) __debugbreak();


static float q_sqrt(float number) {
		int i;
		float x2, y;
		constexpr float threehalfs = 1.5;

		x2 = number * 0.5F;
		y = number;
		i = *(long*)&y;                       // evil floating point bit level hacking
		i = 0x5f3759df - (i >> 1);               // what the fuck? 
		y = *(float*)&i;
		y = y * (threehalfs - (x2 * y * y));   // 1st iteration
	//	y  = y * ( threehalfs - ( x2 * y * y ) );   // 2nd iteration, this can be removed

		return y;
}


template<std::size_t nDims, typename T = double>
class VectorNd {
	T data[nDims];
	T* end;
public:
	VectorNd() {
		static_assert(nDims != 0, "Cant use 0 dimentional VectorNd");
		T* iter = data;
		end = data + nDims;
		do {
			*iter = 0;
		} while (++iter < end);
	}

	
	VectorNd(const VectorNd<nDims, T>& other) {
		for (int i = 0; i < nDims; ++i) {
			data[i] = other.data[i];
		}
		end = data + nDims;
		
	}

	template<typename U>
	VectorNd(const VectorNd<nDims, U>& other) {
		for (int i = 0; i < nDims; ++i) {
			data[i] =static_cast<U>(other.get(i));
		}
		end = data + nDims;

	}

	template<typename ... Targs>
	VectorNd(T dim0, Targs ... Dims) {
		//std::cout << nDims << std::endl;
		//static_assert(nDims != 0);
		data[0] = dim0;
		set(1, Dims...);
	}

	void set(int index, T val) {
		assert(!(index < 0 || index >= nDims), "Error: index out of range");
		data[index] = val;
	}
	
	T get(int index) const {
		return data[index];
	}

	T& operator[](int index) { return data[index]; }

	T mag() const  {
		T magn = 0;
		for (int i = 0; i < nDims; i++) magn += data[i] * data[i];
		return sqrt(magn);
	}

	T sqareMag() const {
		T magn = 0;
		for (int i = 0; i < nDims; i++) magn += data[i] * data[i];
		return magn;
	}
	
	VectorNd<nDims, T>& norm() {
		T magnitude = mag();
		if(magnitude != 0) for (int i = 0; i < nDims; i++) data[i] /= magnitude;
		return *this;
	}

	VectorNd<nDims, T> getNorm() {
		VectorNd<nDims, T> n = *this;
		T magnitude = mag();
		if (magnitude != 0) for (int i = 0; i < nDims; i++) n[i] /= magnitude;
		return n;
	}
	
	VectorNd<nDims, T>& qNorm() {
		double inverseMagnitude = q_sqrt(mag());
		std::cout << inverseMagnitude << std::endl;
		for (int i = 0; i < nDims; i++) data[i] *= inverseMagnitude;
		for (int i = 0; i < nDims; i++) std::cout << data[i] << std::endl;
		return *this;
	}


	template<std::size_t dimN, typename V, typename U>
	friend auto dot(const VectorNd<dimN, V>& vec1, const VectorNd<dimN, U>& vec2) -> decltype(vec1.get(0) * vec2.get(0));
	template<typename V, typename U>


	friend VectorNd<3, decltype((V)1 * (U)1)> cross(const VectorNd<3, V>& a, const VectorNd<3, U>& b);

	template<std::size_t dimN, typename U>
	friend U abs(const VectorNd<dimN, U>& vec);

	template<std::size_t dimN, typename U>
	friend std::ostream& operator<< (std::ostream& console, const VectorNd<dimN, U>& vec);

	template<typename U>
	VectorNd<nDims, T>& operator = (const VectorNd<nDims, U>& other) {
		//static_assert(std::is_same<T, decltype((T)1 + (U)1)>::value, "[ERROR] VectorNd::operator = (const VectorNd<nDims, U>& other), Dataloss when casting from U to T");
		//for (int i = 0; i < nDims; i++) data[i] = other.data[i];
		for (int i = 0; i < nDims; i++) data[i] = other.get(i);
		return *this;
	}

	VectorNd<nDims, T>& operator = (const VectorNd<nDims, T>& other) {
		memcpy(data, &other.data, sizeof(T) * nDims);
		return *this;
	}

	template<typename U>
	VectorNd<nDims, decltype((T)1 + (U)1)> operator + (const VectorNd<nDims, U>& other) const {
		VectorNd < nDims, decltype((T)1 + (U)1)> result;
		for (int i = 0; i < nDims; i++) result[i] = data[i] + other.get(i);
		return result;
	}
	
	template<typename U>
	VectorNd<nDims, decltype((T)1 - (U)1)> operator - (const VectorNd<nDims, U>& other) const  {
		VectorNd < nDims, decltype((T)1 + (U)1)> result;
		for (int i = 0; i < nDims; i++) result[i] = data[i] - other.data[i];
		return result;
	}

	VectorNd<nDims, T> operator -() const {
		VectorNd<nDims, T> result;
		for (int i = 0; i < nDims; i++) result[i] = -data[i];
		return result;
	}

	template<typename U>
	VectorNd<nDims, T>& operator += (const VectorNd<nDims, U>& other) {
		for (int i = 0; i < nDims; i++) data[i] += other.get(i);
		return *this;
	}

	template<typename U>
	VectorNd<nDims, T>& operator -= (const VectorNd<nDims, U>& other) {
		for (int i = 0; i < nDims; i++) data[i] -= other.data[i];
		return *this;
	}

	template<typename U>
	VectorNd<nDims, decltype((T)1 * (U)1)> operator * (U num) const {
		VectorNd<nDims, decltype((T)1 + (U)1)> product;
		for (int i = 0; i < nDims; i++) {
			product[i] = data[i] * num;
		}
		return product;
	}

	template<typename U>
	VectorNd<nDims, decltype((T)1 / (U)1)> operator / (U num) const {
		VectorNd<nDims, decltype((T)1 + (U)1)> product;
		for (int i = 0; i < nDims; i++) {
			product[i] = data[i] / num;
		}
		return product;
	}

	template<typename U>
	VectorNd<nDims, T>& operator *= (U num) {
		for (int i = 0; i < nDims; i++) data[i] *= num;
		return *this;
	}

	template<typename U>
	VectorNd<nDims, T>& operator /= (U num) {
		for (int i = 0; i < nDims; i++) data /= num;
		return *this;
	}

	bool operator == (const VectorNd<nDims, T>& other) {
		bool same = true;
		for (int i = 0; i < nDims; i++) {
			same = same && (data[i] == other.data[i]);
		}
		return same;
	}


	/*
	template<typename U>
	VectorNd<nDims, decltype((T)1 + (U)1)> operator () (U val) {
		static_assert(!std::is_pointer<T>::value, "[error] invoking function on non function poiter based VectorNd");

		using retType = decltype((T)1 + (U)1);
		VectorNd<nDims, retType> invocedVector;
		for (int i = 0; i < nDims; i++) invocedVector[i] = data[i](val);
		return invocedVector;
	}*/

private:
	template<typename ... Targs>
	void set(int index, T first, Targs ... Margs) {
		assert(!(index < 0 || index >= nDims));
		data[index] = first;

		set(index + 1, Margs...);
	}

};

template<std::size_t dimN, typename U>
std::ostream& operator<< (std::ostream& console, const VectorNd<dimN, U>& vec) {
	console << '[';
	for (int i = 0; i < dimN-1; i++) console << vec.data[i] << ", ";
	console << vec.data[dimN - 1];
	console << ']';
	return console;
}

template<std::size_t dimN, typename V, typename U>
auto dot(const VectorNd<dimN, V>& vec1, const VectorNd<dimN, U>& vec2) -> decltype((V)1 * (U)1) {
	
	auto product = vec1[0]*vec2[0];
	for(int i = 1; i < dimN; i++){
		product += vec1[i] * vec2[i];
	}

	return product;
}

template<std::size_t dimN, typename V>
V dot(const VectorNd<dimN, V>& vec1, const VectorNd<dimN, V>& vec2) {

	V product = vec1.get(0) * vec2.get(0);
	for (int i = 1; i < dimN; i++) {
		product += vec1.get(i) * vec2.get(i);
	}

	return product;
}


template<std::size_t dimN, typename U>
U abs(const VectorNd<dimN, U>& vec) {
	return vec.mag();
}

template<typename V, typename U>
VectorNd<3, decltype((V)1 * (U)1)> cross(const VectorNd<3, V>& a, const VectorNd<3, U>& b) {
	VectorNd<3, decltype((V)1 * (U)1)> orthogonalVec;
	orthogonalVec[0] = a.data[1] * b.data[2] - a.data[2] * b.data[1];
	orthogonalVec[1] = a.data[2] * b.data[0] - a.data[0] * b.data[2];
	orthogonalVec[2] = a.data[0] * b.data[1] - a.data[1] * b.data[0];
	return orthogonalVec;
}

typedef VectorNd<3, float> Vector3f;
typedef VectorNd<3, double> Vector3d;
#endif


template<typename T>
VectorNd<3, T> rotateVecAroundVecAx(VectorNd<3, T> vec, VectorNd<3, T> vecAx, float theta) {

	VectorNd<3, T> ap = vecAx * (dot(vec, vecAx) / dot(vecAx, vecAx));
	VectorNd<3, T> ao = vec - ap;

	VectorNd<3, T> a = vec;
	if (ao.mag() == 0) return a;
	VectorNd<3, T> orth = cross(vecAx, ao);

	T x1 = cos(theta) / (ao.mag());
	T x2 = sin(theta) / (orth.mag());


	VectorNd<3, T> aor = (ao * x1 + orth * x2) * ao.mag();

	a = ap + aor;
	return a;
	//__debugbreak();
}