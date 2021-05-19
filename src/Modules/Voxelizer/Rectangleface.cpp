#include "Rectangleface.hpp"

Rectangleface::Rectangleface()
{
}

Rectangleface::Rectangleface(int a, int b, int c, int d) :  a(a), b(b), c(c), d(d)
{
	uv1 = 0;
	uv2 = 0;
	uv3 = 0;
	uv4 = 0;
}

Rectangleface::Rectangleface(int a, int b, int c, int d, int normale, int uv1, int uv2, int uv3, int uv4 ) : a(a), b(b), c(c), d(d), nm(normale), uv1(uv1), uv2(uv2), uv3(uv3), uv4(uv4)
{
}

