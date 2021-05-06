﻿#include "Voxelizer.hpp"
#include <vector>
#include "filters/raytracing/RayTracing.hpp"
#include "filters/raytracing/Hit.hpp"
#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>

Voxelizer::Voxelizer(std::string name) : Module(name)
{

}

void Voxelizer::init(int mapSizeX, int mapSizeY, int horizontalStep, int gridmode, bool material, bool mode)
{
	this->mapsize.x = mapSizeX;
	this->mapsize.y = mapSizeY;
	this->maxHeight = maxHeight;
	this->minHeight = minHeight;
	this->horizontalStep = horizontalStep;
	this->offsetX = offsetX;
	this->offsetY = offsetY;
	for (int i = 0; i < mapSizeX; i++) {
		for (int j = 0; j < mapSizeY; j++) {
			tiles.push_back(TileVoxel(0.0));
		}
	}
	if(scale)
		this->scale = scale;
	if(gridmode)
		this->gridmode = gridmode;
	normalelist.push_back(Normales(1, 0, 0));
	normalelist.push_back(Normales(-1, 0, 0));
	normalelist.push_back(Normales(0, 1, 0));
	normalelist.push_back(Normales(0, -1, 0));
	normalelist.push_back(Normales(0, 0, 1));
	normalelist.push_back(Normales(0, 0, -1));
	// UV ground
	uvlist.push_back(UV(0.125000, 0.500000));
	uvlist.push_back(UV(0.375000, 0.500000));
	uvlist.push_back(UV(0.375000, 0.750000));
	uvlist.push_back(UV(0.125000, 0.750000));
	// UV bat
	uvlist.push_back(UV(0.125000, 0.250000));
	uvlist.push_back(UV(0.375000, 0.250000));
	uvlist.push_back(UV(0.375000, 0.500000));
	uvlist.push_back(UV(0.125000, 0.500000));

}

void Voxelizer::compute(CityGMLTriangulate* cityGMLTriangulate)
{


	offsetX = cityGMLTriangulate->getXmin() - 2;
	offsetY = cityGMLTriangulate->getYmin() - 2;
	std::cout << std::fixed << "offSetX = " << offsetX << std::endl;
	std::cout << std::fixed << "offSetY = " << offsetY << std::endl;
	double lx = cityGMLTriangulate->getXmax() - offsetX + 2;
	double ly = cityGMLTriangulate->getYmax() - offsetY + 2;
	std::cout << "lx = " << lx << std::endl;
	std::cout << "ly = " << ly << std::endl;	
	double zMin = cityGMLTriangulate->getZmin();


	/*int offset = 85;
	int offset2 = 85;*/
	std::vector<Ray*> rays;

	//lancer un rayon sur chaque points d'un grille pr�d�fini
	for (int i = 0; i <mapsize.x; i++) {
		for (int j = 0; j< mapsize.y; j++) {
			//std::cout <<"coordonn�es "<< this->scale* i<< " y =  " << this->scale * j << std::endl;
			float divx = static_cast<float>(i) / static_cast<float>(mapsize.x);
			float divy = static_cast<float>(j) / static_cast<float>(mapsize.y);
			double posX = offsetX + (divx * lx);
			double posY = offsetY + (divy * ly);
			TVec3d position(posX , posY, zMin);
			TVec3d direction(0, 0, 1);
			rays.push_back(new Ray(position, direction, j + (i*mapsize.y)));
		}
	}
	std::cout << "rays :" << rays.size() << std::endl;
	//TVec3d position(125, 175, 1);
	//TVec3d direction(0, 0, -1);
	//rays.push_back(new Ray(position, direction, 0));
	//std::cout << "hey2 ray size: "<< rays.size() << std::endl;

	sizeStep = (maxHeight - minHeight)/ horizontalStep;

	//Recup�rer les hit des points pour r�aliser une height map
	std::vector<Hit*> hits = *RayTracing(cityGMLTriangulate->getTriangleList(), rays, false);
	std::cout << "hit numbers:  " << hits.size() << std::endl;
	for (Hit* hit : hits) {
		int height = maxHeight - hit->distance;
		int delta = height;
		tiles.at(hit->ray.id).height = hit->distance;
		//if (hit->intersect) {

			//if (hit->distance <= (maxHeight - minHeight )) {

			//	//float mod = height % sizeStep;
			//	//if (mod == 0) 
			//	//	delta = height;
			//	//} else if (mod >= float(sizeStep / 2)) {
			//	//	delta = height + (1- mod);

			//	//}
			//	//else {
			//	//	delta = height - (height % sizeStep);

			//	//}
			//	int index = (hit->point.x / this->scale) + (hit->point.y / this->scale * hit->point.x / this->scale);
			//	
			//	if (delta != 0) {
			//		tiles.at(index).type = Building;
			//	}
			//	else {
			//		tiles.at(index).type = Ground;
			//	}
			//}
			//else {
			//	
			//	tiles.at(index).type = Ground;
			//}
		//}
	}
	std::cout << "tilesize : " << tiles.size()  << std::endl;

	for (int i = 0; i < mapsize.x; i++) {
		for (int j = 0; j < mapsize.y; j++) {
			std::cout << std::fixed << std::setprecision(0)<< tiles.at(j + i * mapsize.y).height << "|";
		}
		std::cout << std::endl;
	} 


	rectangulize();

	

}

void Voxelizer::rectangulize()
{

	//creer la face du haut a partir de la height map
	//for (int i = 0; i < mapsize.x; i++) {
	//	for (int j = 0; j < mapsize.y; j++) {
	//		int currentIndex = j + i * mapsize.y;
	//		int h = tiles.at(currentIndex).height;
	//		vertexlist.push_back(TVec3d(i, j, h));
	//		vertexlist.push_back(TVec3d(i + 1, j, h));
	//		vertexlist.push_back(TVec3d(i + 1, j + 1, h));
	//		vertexlist.push_back(TVec3d(i, j + 1, h));
	//		int indice = vertexlist.size();

	//		if (tiles.at(currentIndex).type == Ground) {
	//			tiles.at(j + i * mapsize.y).top = Rectangleface(indice - 1, indice - 2, indice - 3, indice - 4, 2,0,1,2,3);
	//		}
	//		else {
	//			tiles.at(j + i * mapsize.y).top = Rectangleface(indice - 1, indice - 2, indice - 3, indice - 4, 2,4,5,6,7);
	//		}
	//	}
	//}
	
	for (int i = 0; i < mapsize.x; i++) {
		for (int j = 0; j < mapsize.y; j++) {
			int currentIndex = j + i * mapsize.y;
			int h = tiles.at(currentIndex).height;


			TVec3d a(i, j, h);
			TVec3d b(i + 1, j, h);
			TVec3d c(i + 1, j + 1, h);
			TVec3d d(i, j + 1, h);

			bool usePredj = false;
			if (j > 0) {
				if (a == vertexlist.at(tiles.at(currentIndex-1).top.d) && b == vertexlist.at(tiles.at(currentIndex - 1).top.c)) {
					usePredj = true;
				}
			}
			bool usePredi = false;
			if (i > 0) {
				if (d == vertexlist.at(tiles.at(currentIndex - mapsize.y).top.c)) {
					usePredi = true;
				}
			}
			

			if (usePredj){
				//cas ou j-1 == j
				vertexlist.push_back(c);
				if (usePredi) {
					int indice = vertexlist.size();
					tiles.at(currentIndex).top = Rectangleface(tiles.at(currentIndex - 1).top.d, 
																tiles.at(currentIndex - 1).top.c, 
																indice - 1,
																tiles.at(currentIndex - mapsize.x).top.c,
																2, 0, 1, 2, 3);
				}
				else {
					vertexlist.push_back(d);
					int indice = vertexlist.size();
					tiles.at(currentIndex).top = Rectangleface(tiles.at(currentIndex - 1).top.d, 
																tiles.at(currentIndex - 1).top.c, 
																indice - 2, 
																indice - 1, 
																2, 0, 1, 2, 3);
				}

			} else {
				//cas ou i-1 == i
				if (usePredi) {
					vertexlist.push_back(a);
					vertexlist.push_back(b);
					vertexlist.push_back(c);
					int indice = vertexlist.size();
					tiles.at(currentIndex).top = Rectangleface(indice - 3, 
																indice - 2, 
																indice - 1, 
																tiles.at(currentIndex - mapsize.x).top.c, 
																2, 0, 1, 2, 3);
				}
				else {
					vertexlist.push_back(a);
					vertexlist.push_back(b);
					vertexlist.push_back(c);
					vertexlist.push_back(d);
					int indice = vertexlist.size();
					tiles.at(currentIndex).top = Rectangleface(indice - 4, 
																indice - 3, 
																indice - 2, 
																indice - 1, 
																2, 0, 1, 2, 3);
				}
			}
		}
	}
	
	std::cout << "hey4" << std::endl;

	std::cout << "hey5" << std::endl;
	//a faire : faire une fonction qui gere tout les cot�s de maniere g�n�rique
	//relier la diff�rentes faces bas� sur la hauteur entres elles
	//R�alis� en damier pour optimiser
	if (gridmode == 0) {
		for (int i = 0; i < mapsize.x; i++) {
			for (int j = 0; j < mapsize.y; j++) {

				int index = i * j + i;
				std::vector<Rectangleface> columnRight;
				std::vector<Rectangleface> columnBottom;
				// 1. cas horizontal
				// 1.1 il a un voisin a droite
				if (j < mapsize.y - 1) {
					int deltaheight = tiles.at(index).height - tiles.at(index + 1).height;

					if (deltaheight > 0) {
						// 1.1.1 il a un voisin plus petit
						//instancie 

						//Les points du bas
						int newb = tiles.at(index + 1).top.a;
						int newd = tiles.at(index + 1).top.c;
						for (int k = 1; k < deltaheight - 1; k++) {
							//les points du milieu
							TVec3d vecB = vertexlist.at(newb);
							//new a
							vertexlist.push_back(TVec3d(vecB.x, vecB.y + k * sizeStep, vecB.z));
							TVec3d vecD = vertexlist.at(newd);
							//new c
							vertexlist.push_back(TVec3d(vecD.x, vecD.y + k * sizeStep, vecD.z));

							int indice = vertexlist.size();
							normalelist.push_back(Normales(1, 0, 0));
							tiles.at(index).pushRectangleFaceRight(Rectangleface(indice - 2, newb, indice - 1, newd, 0, 4, 5, 6, 7));
							newb = indice - 1;
							newd = indice - 2;
						}
						//Les points du haut
						int newa = tiles.at(index).top.b;
						int newc = tiles.at(index).top.d;
						tiles.at(index).pushRectangleFaceRight(Rectangleface(newa, newb, newc, newd, 0, 4, 5, 6, 7));

					}
					else if (deltaheight < 0) {
						// 1.1.2 il a un voisin plus grand

						//Les points du bas
						int newa = tiles.at(index).top.b;
						int newc = tiles.at(index).top.d;
						for (int k = 1; k < deltaheight - 1; k++) {
							//les points du milieu
							TVec3d vecA = vertexlist.at(newa);
							//new a
							vertexlist.push_back(TVec3d(vecA.x, vecA.y + k * sizeStep, vecA.z));
							TVec3d vecC = vertexlist.at(newc);
							//new c
							vertexlist.push_back(TVec3d(vecC.x, vecC.y + k * sizeStep, vecC.z));

							int indice = vertexlist.size();
							normalelist.push_back(Normales(-1, 0, 0));
							tiles.at(index).pushRectangleFaceRight(Rectangleface(newa, indice - 2, newc, indice - 1, 1, 4, 5, 6, 7));
							newa = indice - 1;
							newc = indice - 2;
						}
						//Les points du haut
						int newb = tiles.at(index + 1).top.a;
						int newd = tiles.at(index + 1).top.c;
						tiles.at(index).pushRectangleFaceRight(Rectangleface(newa, newb, newc, newd, 1, 4, 5, 6, 7));
					}
				}
				// 2. vertical
				// 2.1 il a un voisin en dessous
				if (i < mapsize.x - 1) {
					int deltaheight = tiles.at(index).height - tiles.at(index + mapsize.y).height;
					if (deltaheight > 0) {
						// 1.1.1 il a un voisin plus petit

						//Les points du bas

						int newc = tiles.at(index + mapsize.y).top.a;
						int newd = tiles.at(index + mapsize.y).top.b;
						for (int k = 1; k < deltaheight - 1; k++) {
							//les points du milieu 
							TVec3d vecC = vertexlist.at(newc);
							//new a
							vertexlist.push_back(TVec3d(vecC.x, vecC.y + k * sizeStep, vecC.z));
							TVec3d vecD = vertexlist.at(newd);
							//new b
							vertexlist.push_back(TVec3d(vecD.x, vecD.y + k * sizeStep, vecD.z));

							int indice = vertexlist.size();

							tiles.at(index).pushRectangleFaceDown(Rectangleface(indice - 2, indice, newc, newd, 4, 4, 5, 6, 7));
							newc = indice - 1;
							newd = indice - 2;
						}
						//Les points du haut
						int newa = tiles.at(index).top.c;
						int newb = tiles.at(index).top.d;
						tiles.at(index).pushRectangleFaceDown(Rectangleface(newa, newb, newc, newd, 4, 4, 5, 6, 7));

					}
					else if (deltaheight < 0) {
						// 1.1.2 il a un voisin plus grand

						//Les points du bas
						int newc = tiles.at(index).top.c;
						int newd = tiles.at(index).top.d;
						for (int k = 1; k < deltaheight - 1; k++) {
							//les points du milieu
							TVec3d vecC = vertexlist.at(newc);
							//new a
							vertexlist.push_back(TVec3d(vecC.x, vecC.y + k * sizeStep, vecC.z));
							TVec3d vecD = vertexlist.at(newd);
							//new b
							vertexlist.push_back(TVec3d(vecD.x, vecD.y + k * sizeStep, vecD.z));

							int indice = vertexlist.size();
							tiles.at(index).pushRectangleFaceDown(Rectangleface(indice - 2, indice - 1, newc, newd, 5,4,5,6,7));
							newc = indice - 1;
							newd = indice - 2;
						}
						//Les points du haut
						int newa = tiles.at(index + 1).top.a;
						int newb = tiles.at(index + 1).top.b;
						tiles.at(index).pushRectangleFaceDown(Rectangleface(newa, newb, newc, newd, 5, 4, 5, 6, 7));
					}
				}
			}
		}
	}
	else if(gridmode == 1) {
		for (int i = 0; i < mapsize.x; i++) {
			for (int j = 0; j < mapsize.y; j++) {
				int index = mapsize.x * j + i;
				if (i < mapsize.x - 1) {
					int deltaheight = tiles.at(index).height - tiles.at(index + 1).height;
					//si >0 alors index plus haut

					if (deltaheight > 0) {

						int newa = tiles.at(index + 1).top.a;
						int newb = tiles.at(index + 1).top.b;
						int newc = tiles.at(index).top.c;
						int newd = tiles.at(index).top.d;
						tiles.at(index).pushRectangleFaceRight(Rectangleface(newa, newb, newc, newd, 4, 4, 5, 6, 7));
					}
					else if (deltaheight < 0) {

						int newa = tiles.at(index + 1).top.a;
						int newb = tiles.at(index + 1).top.b;
						int newc = tiles.at(index).top.c;
						int newd = tiles.at(index).top.d;
						tiles.at(index).pushRectangleFaceRight(Rectangleface(newa, newb, newc, newd, 5, 4, 5, 6, 7));
					}
				}
				if (j < mapsize.y - 1) {
					int deltaheight = tiles.at(index).height - tiles.at(index + mapsize.y).height;
					if (deltaheight > 0) {
						int newa = tiles.at(index + mapsize.y).top.a;
						int newb = tiles.at(index).top.b;
						int newc = tiles.at(index).top.c;
						int newd = tiles.at(index + mapsize.y).top.d;
						tiles.at(index).pushRectangleFaceDown(Rectangleface(newa, newb, newc, newd, 0, 4, 5, 6, 7));
					}
					else if (deltaheight < 0) {
						int newa = tiles.at(index + mapsize.y).top.a;
						int newb = tiles.at(index).top.b;
						int newc = tiles.at(index).top.c;
						int newd = tiles.at(index + mapsize.y).top.d;
						tiles.at(index).pushRectangleFaceDown(Rectangleface(newa, newb, newc, newd, 1, 4, 5, 6, 7));
					}
				}
			}
		}
	}
	std::cout << "hey6" << std::endl;
	printObj();
}

void Voxelizer::printObj()
{ 
	std::ofstream myfile;
	myfile.open("object.obj");
	myfile.clear();
	myfile << "# Blender v2.91.2 OBJ File: ''" << std::endl;
	myfile << "#www.blender.org" << std::endl;
	myfile << "mtllib test.mtl" << std::endl;
	myfile << "o Ville" << std::endl;
	//liste des faces
	for (int i = 0; i < vertexlist.size(); i++) {
		myfile << "v " << vertexlist.at(i).x << " " << vertexlist.at(i).z << " " << vertexlist.at(i).y << std::endl;
	}

	//liste des coordonees de texture
	for (int i = 0; i < uvlist.size(); i++) {
		myfile << "vt " << uvlist.at(i).a << " " << uvlist.at(i).b  << std::endl;
	}

	//liste des normales
	for (int i = 0; i < normalelist.size(); i++) {
		myfile << "vn " << normalelist.at(i).a << " " << normalelist.at(i).b << " "<< normalelist.at(i).c << std::endl;
	}

	myfile << "usemtl Material.001" << std::endl;
	myfile << "s off" << std::endl;


	//liste des faces
	for (int i = 0; i < tiles.size(); i++) {
		if (material) {
			if (tiles.at(i).type == Ground)
			{
				myfile << "usemtl Material.001" << std::endl;
			}
			else {
				myfile << "usemtl Material.002" << std::endl;
			}
		}
		myfile << "f " << tiles.at(i).top.d +  1<< "/" << tiles.at(i).top.uv4 +1 << "/" << tiles.at(i).top.nm +1 << " " <<
				tiles.at(i).top.c +1 << "/" << tiles.at(i).top.uv3 + 1<< "/" << tiles.at(i).top.nm +1 << " " <<
				tiles.at(i).top.b +1 << "/" << tiles.at(i).top.uv2 + 1<< "/" << tiles.at(i).top.nm +1<< " " <<
				tiles.at(i).top.a +1 << "/" << tiles.at(i).top.uv1 + 1 << "/" << tiles.at(i).top.nm +1<< " " << std::endl;
		


		for (int j = 0; j < tiles.at(i).getSizeRightRF(); j++) {
			myfile << "f " << tiles.at(i).getRightRF(j).a +1<< "/" << tiles.at(i).getRightRF(j).uv1+1 << "/" << tiles.at(i).getRightRF(j).nm + 1<< " " <<
				tiles.at(i).getRightRF(j).b + 1 << "/" << tiles.at(i).getRightRF(j).uv2 + 1 << "/" << tiles.at(i).getRightRF(j).nm + 1<< " " <<
				tiles.at(i).getRightRF(j).c + 1 << "/" << tiles.at(i).getRightRF(j).uv3 + 1<< "/" << tiles.at(i).getRightRF(j).nm + 1 << " " <<
				tiles.at(i).getRightRF(j).d + 1 << "/" << tiles.at(i).getRightRF(j).uv4 + 1<< "/" << tiles.at(i).getRightRF(j).nm + 1 << " " << std::endl;
		}



		for (int j = 0; j < tiles.at(i).getSizeDownRF(); j++) {
			myfile << "f " << tiles.at(i).getDownRF(j).a + 1<< "/" << tiles.at(i).getDownRF(j).uv1 + 1<< "/" << tiles.at(i).getDownRF(j).nm + 1 << " " <<
				tiles.at(i).getDownRF(j).b + 1 << "/" << tiles.at(i).getDownRF(j).uv2 + 1 << "/" << tiles.at(i).getDownRF(j).nm + 1<< " " <<
				tiles.at(i).getDownRF(j).c + 1<< "/" << tiles.at(i).getDownRF(j).uv3 + 1<< "/" << tiles.at(i).getDownRF(j).nm + 1<< " " <<
				tiles.at(i).getDownRF(j).d + 1<< "/" << tiles.at(i).getDownRF(j).uv4 + 1 << "/" << tiles.at(i).getDownRF(j).nm +1  << " " << std::endl;
		}
	}
	myfile.close();
}

void Voxelizer::printvertices()
{

}

