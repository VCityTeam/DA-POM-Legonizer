#pragma once

#include "../../CityModel/Vecs.hpp"
// Include the string library
#include <string>
#include "UV.hpp"
#include "Normales.hpp"

/*
* @brief contient les indices des vertex, normale et uv
*/
struct Rectangleface {
	public : 
		Rectangleface();
		Rectangleface(int a, int b, int c, int d);
		Rectangleface(int a, int b, int c, int d, int normale, int uv1, int uv2, int uv3, int uv4);
		int a;
		int b;
		int c;
		int d;
		int uv1;
		int uv2;
		int uv3;
		int uv4;
		int nm;
};
