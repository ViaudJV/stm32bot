/*
 * vector.h
 *
 *  Created on: 4 août 2015
 *      Author: jul
 */

#ifndef VECTOR2_H_
#define VECTOR2_H_

#include <math.h>


class vector2 {

public:
	vector2()
	{
		x = 0;
		y = 0;
	}

	vector2(float X, float Y)
	{
		x = X;
		y = Y;
	}

	inline float norm()
	{
		return sqrtf(x * x + y * y);
	}

	inline float norm2()
	{
		return x * x + y * y;
	}

	inline vector2 operator+(const vector2 b)
	{
		return vector2(x + b.x, y + b.y);
	}

	inline vector2 operator*(float k)
	{
		return vector2(k * x, k * y);
	}

	inline vector2 operator/( float k)
	{
		return vector2(x / k, y / k);
	}

	inline vector2 operator-(const vector2 b)
	{
		return vector2(x-b.x, y-b.y);
	}

	//!< @brief calcul le produit avec le vecteur v
	//!< @param vecteur v
	//!< @return produit calculé avec les positions en mm
	inline vector2 operator*(const vector2 v)
	{
		return vector2(x * v.x, y * v.y);
	}

	//!< @brief calcul le produit scalaire avec le vecteur v
	//!< @param vecteur v
	//!< @return produit scalaire calculé avec les positions en mm
	inline float scalarProd(const vector2& v)
	{
		return x * v.x + y * v.y;
	}

	//!< @function fx_Vect2_vector_product_z
	//!< @brief calcule la compose sur Oz du produit vectoriel avec v (appartenant à (Ox,Oy))
	//!< @param vecteur v
	//!< @return composante sur Oz du produit vectoriel calculé avec les positions en mm
	inline float crossProd_z(const vector2& v)
	{
		return x * v.y - y * v.x;
	}

	float x;
	float y;
};

inline vector2 operator*(float k, vector2 a)
{
return vector2(k * a.x, k * a.y);
}

inline vector2 operator-(vector2 a)
{
return vector2(-a.x, -a.y);
}


#endif /* VECTOR2_H_ */
