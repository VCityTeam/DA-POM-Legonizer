#include "Heightmap.hpp"
#include <vector>
#include "filters/raytracing/RayTracing.hpp"
#include "filters/raytracing/Hit.hpp"
#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>

Heightmap::Heightmap(std::string name) : Module(name)
{

}

void Heightmap::init(int mapSizeX, int mapSizeY, int horizontalStep, bool debug)
{
	this->mapsize.x = mapSizeX;
	this->mapsize.y = mapSizeY;
	this->horizontalStep = horizontalStep;
	this->debug = debug;

	for (int i = 0; i < mapSizeX; i++) {
		for (int j = 0; j < mapSizeY; j++) {
			tiles.push_back(TileHeight(0.0));
		}
	}
}

void Heightmap::computeHeightMap(CityGMLTriangulate* cityGMLTriangulate)
{


	int offsetX = cityGMLTriangulate->getXmin() - 2;
	int offsetY = cityGMLTriangulate->getYmin() - 2;

	double lx = cityGMLTriangulate->getXmax() - offsetX + 2;
	double ly = cityGMLTriangulate->getYmax() - offsetY + 2;

	double zMin = cityGMLTriangulate->getZmin();
	double zMax = cityGMLTriangulate->getZmax();

	if (debug) {
		std::cout << std::fixed << "offSetX = " << offsetX << std::endl;
		std::cout << std::fixed << "offSetY = " << offsetY << std::endl;
		std::cout << "lx = " << lx << std::endl;
		std::cout << "ly = " << ly << std::endl;
	}

	sizeStepX = (static_cast<float>(1) / static_cast<float>(mapsize.x)) * lx;
	sizeStepY = (static_cast<float>(1) / static_cast<float>(mapsize.y)) * ly;


	int nbrays = mapsize.x * mapsize.y;
	int progressionPart = nbrays / 20;
	std::cout << std::endl << ":::::::::: Launching "<< nbrays <<" rays in multithread ::::::::::" << std::endl;
	std::vector<Ray*> rays;
	//lancer un rayon sur chaque points d'un grille pr�d�fini
	for (int i = 0; i <mapsize.x; i++) {
		for (int j = 0; j< mapsize.y; j++) {
			float divx = static_cast<float>(i) / static_cast<float>(mapsize.x);
			float divy = static_cast<float>(j) / static_cast<float>(mapsize.y);
			double posX = offsetX + (divx * lx);
			double posY = offsetY + (divy * ly);
			TVec3d position(posX , posY, zMax);
			TVec3d direction(0, 0, -1);
			rays.push_back(new Ray(position, direction, j + (i * mapsize.y)));
		}
	}

	sizeStep = (zMax - zMin)/ horizontalStep;
	std::cout << std::endl << "sizeStepX = " << sizeStepX << std::endl;
	std::cout << std::endl << "sizeStepY = " << sizeStepY << std::endl;
	if(debug)
		std::cout <<std::endl<< "sizeStep = " << sizeStep << std::endl;
	std::cout << std::endl << "Progression of thread 0 " << std::endl;
	//Recup�rer les hit des points pour r�aliser une height map
	std::vector<Hit*> hits = *RayTracing(cityGMLTriangulate->getTriangleList(), rays, false);
	std::cout << ":::::::::: Iterating on Hit ::::::::::" << std::endl;
	for (Hit* hit : hits) {
		double height = (float)(zMax-zMin) - hit->distance;
		double delta = 0.0;
		double mod = std::fmod(height, sizeStep);
		if (mod < sizeStep / 2) {
			delta = height - mod;
		} else if (mod > sizeStep / 2) {
			delta = height- mod + sizeStep ;
		} else {
			delta = height;
		}

		tiles.at(hit->ray.id).height = delta;
		tiles.at(hit->ray.id).type = Building;


	}

	if (debug) {
		for (int i = 0; i < mapsize.x; i++) {
			for (int j = 0; j < mapsize.y; j++) {
				std::cout << std::fixed << std::setprecision(3) << tiles.at(j + i * mapsize.y).height << "|";
			}
			std::cout << std::endl;
		}
	}



}

void Heightmap::printHeightMap(const std::string filename)
{
	std::cout << ":::::::::: Writing Heightmap in " << filename << "::::::::::" << std::endl;
	std::ofstream myfile;
	myfile.open(filename);
	myfile.clear();
	if (!filename.empty()) {
		for (int i = 0; i < mapsize.x; i++) {
			for (int j = 0; j < mapsize.y; j++) {
				myfile << tiles.at(j + i * mapsize.y).height << ";";
			}
			myfile << std::endl;
		}
	}
	myfile.close();
}

void Heightmap::printHeightMap2(const std::string filename)
{
	std::cout << ":::::::::: Writing Heightmap in " << filename << "::::::::::" << std::endl;
	std::ofstream myfile;
	myfile.open(filename);
	myfile.clear();
	if (!filename.empty()) {
		for (int i = 0; i < mapsize.x; i++) {
			for (int j = 0; j < mapsize.y; j++) {
				myfile << tiles.at(j + i * mapsize.y).height / sizeStep << ";";
			}
			myfile << std::endl;
		}
	}
	myfile.close();
}




