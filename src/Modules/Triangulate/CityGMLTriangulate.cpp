#include "CityGMLTriangulate.hpp"
#include <iostream>
#include <fstream>

CityGMLTriangulate::CityGMLTriangulate(std::string name) : Module(name) {}


void CityGMLTriangulate::initTriangleListCityModel(const citygml::CityModel* cityModel) {
	this->listTriangle = BuildListTriangle(cityModel);

}

void CityGMLTriangulate::initTriangleList(std::string& gmlfile, bool debug) {
    this->listTriangle = BuildListTriangleTile(gmlfile);
    this->debug = debug;
    std::cout << ":::::::::: Triangle List Build ::::::::::" << std::endl;
}

int CityGMLTriangulate::getTriangleListSize()
{
	return listTriangle->getSize();
}

TriangleList* CityGMLTriangulate::getTriangleList()
{
    return listTriangle;
}

void CityGMLTriangulate::printBaseTriangleList(TriangleList* triangleList) {
    std::ofstream myfile;
	myfile.open("output/triangulate.obj");
	myfile.clear();
	myfile << "# Blender v2.91.2 OBJ File: ''" << std::endl;
	myfile << "#www.blender.org" << std::endl;
	myfile << "mtllib test.mtl" << std::endl;
	myfile << "o base" << std::endl;
	
	for (int i = 0; i < triangleList->triangles.size(); i++) {
		myfile << std::fixed << "v " << triangleList->triangles.at(i)->a.x << " " << triangleList->triangles.at(i)->a.y << " " << triangleList->triangles.at(i)->a.z << std::endl
			<< "v " << triangleList->triangles.at(i)->b.x << " " << triangleList->triangles.at(i)->b.y << " " << triangleList->triangles.at(i)->b.z << std::endl
			<< "v " << triangleList->triangles.at(i)->c.x << " " << triangleList->triangles.at(i)->c.y << " " << triangleList->triangles.at(i)->c.z << std::endl;
	}

	myfile << "vt 0 0" << std::endl;
	myfile << "vt 0 1" << std::endl;
	myfile << "vt 1 1" << std::endl;
	
	for (int i = 0; i < triangleList->triangles.size(); i++) {
		myfile << "vn " << triangleList->triangles.at(i)->GetNormal().x << " " << triangleList->triangles.at(i)->GetNormal().y << " " << triangleList->triangles.at(i)->GetNormal().z << std::endl;
	}
	
	myfile << "usemtl Material.001" << std::endl;
	myfile << "s off" << std::endl;
	for (int i = 0; i < triangleList->triangles.size(); i++) {
		myfile << "f " << 1 + i * 3 << "/1/" << i + 1 << " "
			<< 2 + i * 3 << "/2/" << i + 1 << " "
			<< 3 + i * 3 << "/3/" << i + 1 << std::endl;
	}
}

double CityGMLTriangulate::getXmin()
{
    double xMin = listTriangle->triangles.at(0)->a.x;

    for (int i = 0; i < listTriangle->getSize(); i++) {
        if (listTriangle->triangles.at(i)->a.x < xMin) {
            xMin = listTriangle->triangles.at(i)->a.x;
        }
        if (listTriangle->triangles.at(i)->b.x < xMin) {
            xMin = listTriangle->triangles.at(i)->b.x;
        }
        if (listTriangle->triangles.at(i)->c.x < xMin) {
            xMin = listTriangle->triangles.at(i)->c.x;
        }
    }
    if(debug)
        std::cout << "xmin : " << (int)xMin << std::endl;
    return xMin;
}

double CityGMLTriangulate::getXmax()
{
    double xMax = 0;
    for (int i = 0; i < listTriangle->getSize(); i++) {
        if (listTriangle->triangles.at(i)->a.x > xMax) {
            xMax = listTriangle->triangles.at(i)->a.x;
        }
        if (listTriangle->triangles.at(i)->b.x > xMax) {
            xMax = listTriangle->triangles.at(i)->b.x;
        }
        if (listTriangle->triangles.at(i)->c.x > xMax) {
            xMax = listTriangle->triangles.at(i)->c.x;
        }
    }
    if(debug)
        std::cout << "xmax : " << (int)xMax << std::endl;
    return xMax;
}

double CityGMLTriangulate::getYmin()
{
    double yMin = listTriangle->triangles.at(0)->a.y;

    for (int i = 0; i < listTriangle->getSize(); i++) {
        if (listTriangle->triangles.at(i)->a.y < yMin) {
            yMin = listTriangle->triangles.at(i)->a.y;
        }
        if (listTriangle->triangles.at(i)->b.y < yMin) {
            yMin = listTriangle->triangles.at(i)->b.y;
        }
        if (listTriangle->triangles.at(i)->c.y < yMin) {
            yMin = listTriangle->triangles.at(i)->c.y;
        }
    }
    if(debug)
        std::cout << "ymin : " << (int)yMin << std::endl;
    return yMin;
}

double CityGMLTriangulate::getYmax()
{
    double yMax = 0;

    for (int i = 0; i < listTriangle->getSize(); i++) {
        if (listTriangle->triangles.at(i)->a.y > yMax) {
            yMax = listTriangle->triangles.at(i)->a.y;
        }
        if (listTriangle->triangles.at(i)->b.y > yMax) {
            yMax = listTriangle->triangles.at(i)->b.y;
        }
        if (listTriangle->triangles.at(i)->c.y > yMax) {
            yMax = listTriangle->triangles.at(i)->c.y;
        }
    }
    if(debug)
        std::cout << "ymax : " << (int)yMax << std::endl;
    return yMax;
}

double CityGMLTriangulate::getZmin()
{
    double zMin = listTriangle->triangles.at(0)->a.z;

    for (int i = 0; i < listTriangle->getSize(); i++) {
        if (listTriangle->triangles.at(i)->a.z < zMin) {
            zMin = listTriangle->triangles.at(i)->a.z;
        }
        if (listTriangle->triangles.at(i)->b.z < zMin) {
            zMin = listTriangle->triangles.at(i)->b.z;
        }
        if (listTriangle->triangles.at(i)->c.z < zMin) {
            zMin = listTriangle->triangles.at(i)->c.z;
        }
    }
    if(debug)
        std::cout << "zmin : " << (int)zMin << std::endl;
    return zMin;
}

double CityGMLTriangulate::getZmax()
{
    double zMax = 0;

    for (int i = 0; i < listTriangle->getSize(); i++) {
        if (listTriangle->triangles.at(i)->a.z > zMax) {
            zMax = listTriangle->triangles.at(i)->a.z;
        }
        if (listTriangle->triangles.at(i)->b.z > zMax) {
            zMax = listTriangle->triangles.at(i)->b.z;
        }
        if (listTriangle->triangles.at(i)->c.z > zMax) {
            zMax = listTriangle->triangles.at(i)->c.z;
        }
    }
    if(debug)
        std::cout << "zmax : " << (int)zMax << std::endl;
    return zMax;
}