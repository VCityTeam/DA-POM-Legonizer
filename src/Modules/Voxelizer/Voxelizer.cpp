#include "Voxelizer.hpp"
#include <vector>
#include "../Heightmap/filters/raytracing/RayTracing.hpp"
#include "../Heightmap/filters/raytracing/Hit.hpp"
#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>

Voxelizer::Voxelizer(std::string name) : Module(name)
{

}

void Voxelizer::init(int mapSizeX, int mapSizeY, int horizontalStep, int gridmode, bool material, std::vector<TileHeight> tileHeight, bool stepByStep, bool debug)
{
	this->mapsize.x = mapSizeX;
	this->mapsize.y = mapSizeY;
	this->horizontalStep = horizontalStep;
	this->material = material;
	this->debug = debug;
	this->stepByStep = stepByStep;

	for (int i = 0; i < mapSizeX; i++) {
		for (int j = 0; j < mapSizeY; j++) {
			tiles.push_back(TileVoxel(tileHeight.at(j + i * mapSizeY).height));
		}
	}
	tileHeight.clear();

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

void Voxelizer::remesh()
{
	
	std::cout << ":::::::::: Calculating top faces and optimizing ::::::::::" << std::endl;

	for (int i = 0; i < mapsize.x; i++) {
		for (int j = 0; j < mapsize.y; j++) {
			int currentIndex = j + i * mapsize.y;
			double h = tiles.at(currentIndex).height;



			double height = h;
			TVec3d a(i * sizeStepX, j * sizeStepY, height);
			TVec3d b(i * sizeStepX + sizeStepX, j * sizeStepY, height);
			TVec3d c(i * sizeStepX + sizeStepX, j * sizeStepY + sizeStepY, height);
			TVec3d d(i * sizeStepX, j * sizeStepY + sizeStepY, height);

			//Test if the last face in x was at the same height
			bool usePredj = false;
			if (j > 0) {
				if (a == vertexlist.at(tiles.at(currentIndex-1).top.d)) {
					usePredj = true;
				}
			}

			//Test if the last face in y was at the same height
			bool usePredi = false;
			if (i > 0) {
				if (d == vertexlist.at(tiles.at(currentIndex - mapsize.y).top.c)) {
					usePredi = true;
				}
			}

			bool usePredDiag1 = false;
			if (i > 0 && j>0) {
				if (a == vertexlist.at(tiles.at(currentIndex - mapsize.y - 1).top.c)) {
					usePredDiag1 = true;

				}
			}

			bool usePredDiag2 = false;
			if (i > 0 && j < mapsize.y - 1) {
				if (d == vertexlist.at(tiles.at(currentIndex - mapsize.y + 1).top.b)) {
					usePredDiag2 = true;
				}
			}


			if (usePredj){
				//case where j-1 == j
				vertexlist.push_back(c);
				if (usePredi) {
					int indice = vertexlist.size();
					tiles.at(currentIndex).top = Rectangleface(tiles.at(currentIndex - 1).top.d, 
																tiles.at(currentIndex - 1).top.c, 
																indice - 1,
																tiles.at(currentIndex - mapsize.y).top.c,
																2, 0, 1, 2, 3);
				}
				else {
					if (usePredDiag2) {
						int indice = vertexlist.size();
						tiles.at(currentIndex).top = Rectangleface(tiles.at(currentIndex - 1).top.d,
							tiles.at(currentIndex - 1).top.c,
							indice - 1,
							tiles.at(currentIndex - mapsize.y + 1).top.b,
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
				}

			} else {
				//case where i-1 == i
				if (usePredi) {
					vertexlist.push_back(a);
					vertexlist.push_back(b);
					vertexlist.push_back(c);
					int indice = vertexlist.size();
					tiles.at(currentIndex).top = Rectangleface(indice - 3, 
																indice - 2, 
																indice - 1, 
																tiles.at(currentIndex - mapsize.y).top.c, 
																2, 0, 1, 2, 3);
				}
				else {
					if (usePredDiag1 && !usePredDiag2) {
						vertexlist.push_back(b);
						vertexlist.push_back(c);
						vertexlist.push_back(d);
						int indice = vertexlist.size();
						tiles.at(currentIndex).top = Rectangleface(tiles.at(currentIndex - mapsize.y - 1).top.c,
							indice - 3,
							indice - 2,
							indice - 1,
							2, 0, 1, 2, 3);
					}
					else if (usePredDiag2 && !usePredDiag1) {
						vertexlist.push_back(a);
						vertexlist.push_back(b);
						vertexlist.push_back(c);
						int indice = vertexlist.size();
						tiles.at(currentIndex).top = Rectangleface(indice - 3,
							indice - 2,
							indice - 1,
							tiles.at(currentIndex - mapsize.y + 1).top.b,
							2, 0, 1, 2, 3);
					}
					else if (usePredDiag1 && usePredDiag2) {
						vertexlist.push_back(b);
						vertexlist.push_back(c);
						int indice = vertexlist.size();
						tiles.at(currentIndex).top = Rectangleface(tiles.at(currentIndex - mapsize.y - 1).top.c,
							indice - 2,
							indice - 1,
							tiles.at(currentIndex - mapsize.y + 1).top.b,
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
	}

	std::cout << ":::::::::: Calculating vertical faces ::::::::::" << std::endl;
	//a faire : faire une fonction qui gere tout les cot�s de maniere g�n�rique
	//relier la diff�rentes faces bas� sur la hauteur entres elles
	//R�alis� en damier pour optimiser
	if (gridmode == 0) {
		for (int i = 0; i < mapsize.x; i++) {
			for (int j = 0; j < mapsize.y; j++) {

				int index = j + i * mapsize.y;
				// 1. line case
				// 1.1 neighboor on right
				if (j < mapsize.y - 1) {
					double deltaheight = tiles.at(index).height - tiles.at(index + 1).height;

					if (deltaheight > 0) {
						// 1.1.1 neighboor smaller
						//Bottom points
						int newa = tiles.at(index + 1).top.a;
						int newb = tiles.at(index + 1).top.b;
						//Middle points
						for (double k = 1; k * sizeStep <= deltaheight - sizeStep*0.99; k++) {
							
							TVec3d vecA = vertexlist.at(newa);
							//new c
							vertexlist.push_back(TVec3d(vecA.x, vecA.y , vecA.z +  sizeStep));
							TVec3d vecB = vertexlist.at(newb);
							//new d
							vertexlist.push_back(TVec3d(vecB.x, vecB.y , vecB.z +  sizeStep));

							int indice = vertexlist.size();
							tiles.at(index).pushRectangleFaceRight(Rectangleface(newa, newb, indice - 1, indice - 2, 4, 4, 5, 6, 7));
							newa = indice - 2;
							newb = indice - 1;
						}
						// Final point
						int newd = tiles.at(index).top.d;
						int newc = tiles.at(index).top.c;
						tiles.at(index).pushRectangleFaceRight(Rectangleface(newa, newb, newc, newd, 4, 4, 5, 6, 7));

					} else if (deltaheight < 0) {
						// 1.1.2 neighboor higher
						deltaheight = abs(deltaheight);
						//Bottom points
						int newd = tiles.at(index).top.d;
						int newc = tiles.at(index).top.c;
						//Middle points
						for (double k = 1; k * sizeStep<= deltaheight - sizeStep*0.99; k++) {
							TVec3d vecD = vertexlist.at(newd);
							//new a
							vertexlist.push_back(TVec3d(vecD.x, vecD.y, vecD.z + sizeStep));
							TVec3d vecC = vertexlist.at(newc);
							//new c
							vertexlist.push_back(TVec3d(vecC.x, vecC.y, vecC.z + sizeStep));

							int indice = vertexlist.size();
							tiles.at(index).pushRectangleFaceRight(Rectangleface(indice - 2, indice - 1, newc, newd, 5, 4, 5, 6, 7));
							newd = indice - 2;
							newc = indice - 1;
						}
						//Final points
						int newa = tiles.at(index + 1).top.a;
						int newb = tiles.at(index + 1).top.b;
						tiles.at(index).pushRectangleFaceRight(Rectangleface(newa, newb, newc, newd, 5, 4, 5, 6, 7));
					}
				}
				//// 2. column case
				//// 2.1 neighboor on last column
				if (i < mapsize.x - 1) {
					double deltaheight = tiles.at(index).height - tiles.at(index + mapsize.y).height;

					if (deltaheight > 0) {
						// 1.1.1 neighboor smaller

						//Bottom points
						int newa = tiles.at(index + mapsize.y).top.a;
						int newd = tiles.at(index + mapsize.y).top.d;
						//Middle points
						for (double k = 1; k * sizeStep<= deltaheight - sizeStep*0.99; k++) {
							TVec3d vecA = vertexlist.at(newa);
							//new b
							vertexlist.push_back(TVec3d(vecA.x, vecA.y , vecA.z + sizeStep));
							TVec3d vecD = vertexlist.at(newd);
							//new c
							vertexlist.push_back(TVec3d(vecD.x, vecD.y, vecD.z + sizeStep));

							int indice = vertexlist.size();

							tiles.at(index).pushRectangleFaceDown(Rectangleface(newa, indice - 2, indice - 1, newd, 0, 4, 5, 6, 7));
							newa = indice - 2;
							newd = indice - 1;
						}
						//Final points
						int newb = tiles.at(index).top.b;
						int newc = tiles.at(index).top.c;
						tiles.at(index).pushRectangleFaceDown(Rectangleface(newa, newb, newc, newd, 0, 4, 5, 6, 7));

					} else if (deltaheight < 0) {
						// 1.1.2 neighboor higher
						deltaheight = abs(deltaheight);

						//Bottom points
						int newb = tiles.at(index).top.b;
						int newc = tiles.at(index).top.c;
						//Middle points
						for (double k = 1; k * sizeStep <= deltaheight - sizeStep*0.99; k++) {
							//les points du milieu
							TVec3d vecC = vertexlist.at(newb);
							//new a
							vertexlist.push_back(TVec3d(vecC.x, vecC.y, vecC.z + sizeStep));
							TVec3d vecD = vertexlist.at(newc);
							//new b
							vertexlist.push_back(TVec3d(vecD.x, vecD.y, vecD.z + sizeStep));

							int indice = vertexlist.size();
							tiles.at(index).pushRectangleFaceDown(Rectangleface(indice - 2, newb, newc, indice - 1, 1,4,5,6,7));
							newb = indice - 2;
							newc = indice - 1;
						}
						//Final points
						int newa = tiles.at(index + mapsize.y).top.a;
						int newd = tiles.at(index + mapsize.y).top.d;
						tiles.at(index).pushRectangleFaceDown(Rectangleface(newa, newb, newc, newd, 1, 4, 5, 6, 7));
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
					double deltaheight = tiles.at(index).height - tiles.at(index + 1).height;

					if (deltaheight > 0.0) {

						int newa = tiles.at(index + 1).top.a;
						int newb = tiles.at(index + 1).top.b;
						int newc = tiles.at(index).top.c;
						int newd = tiles.at(index).top.d;
						tiles.at(index).pushRectangleFaceRight(Rectangleface(newa, newb, newc, newd, 4, 4, 5, 6, 7));
					}
					else if (deltaheight < 0.0) {

						int newa = tiles.at(index + 1).top.a;
						int newb = tiles.at(index + 1).top.b;
						int newc = tiles.at(index).top.c;
						int newd = tiles.at(index).top.d;
						tiles.at(index).pushRectangleFaceRight(Rectangleface(newa, newb, newc, newd, 5, 4, 5, 6, 7));
					}
				}
				if (j < mapsize.y - 1) {
					double deltaheight = tiles.at(index).height - tiles.at(index + mapsize.y).height;
					if (deltaheight > 0.0) {
						int newa = tiles.at(index + mapsize.y).top.a;
						int newb = tiles.at(index).top.b;
						int newc = tiles.at(index).top.c;
						int newd = tiles.at(index + mapsize.y).top.d;
						tiles.at(index).pushRectangleFaceDown(Rectangleface(newa, newb, newc, newd, 0, 4, 5, 6, 7));
					}
					else if (deltaheight < 0.0) {
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


}

void Voxelizer::printObj(const std::string namefile)
{ 
	std::cout << ":::::::::: Writing in " << namefile << "::::::::::" << std::endl;
	std::ofstream myfile;
	myfile.open(namefile);
	myfile.clear();
	myfile << "# Blender v2.91.2 OBJ File: ''" << std::endl;
	myfile << "#www.blender.org" << std::endl;
	myfile << "mtllib test.mtl" << std::endl;
	myfile << "o Ville" << std::endl;

	//list of vertices
	for (int i = 0; i < vertexlist.size(); i++) {
		myfile << "v " << vertexlist.at(i).x << " " << vertexlist.at(i).z << " " << vertexlist.at(i).y << std::endl;
	}

	//list of textures coordinates
	for (int i = 0; i < uvlist.size(); i++) {
		myfile << "vt " << uvlist.at(i).a << " " << uvlist.at(i).b  << std::endl;
	}

	//list of normales
	for (int i = 0; i < normalelist.size(); i++) {
		myfile << "vn " << normalelist.at(i).a << " " << normalelist.at(i).b << " "<< normalelist.at(i).c << std::endl;
	}

	myfile << "usemtl Material.001" << std::endl;
	myfile << "s off" << std::endl;


	//list of faces
	for (int i = 0; i < tiles.size(); i++) {
		if (material) {
			if (tiles.at(i).type == Ground)
			{
				myfile << "usemtl Material.001" << std::endl;
			}
			else {
				if (stepByStep) {
					//std::cout << tiles.at(i).height << " vs " << max << std::endl;
					if (tiles.at(i).height > max * 0.99 && tiles.at(i).height < max * 1.01) {
						myfile << "usemtl new" << std::endl;
					}
					else {
						myfile << "usemtl Building" << std::endl;
					}
				}
				else {
					myfile << "usemtl Building" << std::endl;
				}
			}
		}
		myfile << "f " << tiles.at(i).top.d +  1<< "/" << tiles.at(i).top.uv4 +1 << "/" << tiles.at(i).top.nm +1 << " " <<
				tiles.at(i).top.c +1 << "/" << tiles.at(i).top.uv3 + 1<< "/" << tiles.at(i).top.nm +1 << " " <<
				tiles.at(i).top.b +1 << "/" << tiles.at(i).top.uv2 + 1<< "/" << tiles.at(i).top.nm +1<< " " <<
				tiles.at(i).top.a +1 << "/" << tiles.at(i).top.uv1 + 1 << "/" << tiles.at(i).top.nm +1<< " " << std::endl;
		

		bool rightmax = false;
		bool downmax = false;
		if (material) {
			if (stepByStep) {
				if (i < tiles.size() - 1) {
					if (tiles.at(i + 1).height == max) {
						if (tiles.at(i).height != max) {
							rightmax = true;
						}
					}
				}
				if (i < tiles.size() - mapsize.y - 1) {
					if (tiles.at(i + mapsize.y).height == max) {
						if (tiles.at(i).height != max) {
							downmax = true;
						}
					}
				}
			}
			
			myfile << "usemtl Building" << std::endl;

		}
		for (int j = 0; j < tiles.at(i).getSizeRightRF(); j++) {
			if (rightmax && j == tiles.at(i).getSizeRightRF() - 1) {
				myfile << "usemtl new" << std::endl;
			}
			else if (tiles.at(i).height == max && stepByStep && j == tiles.at(i).getSizeRightRF() - 1) {
				myfile << "usemtl new" << std::endl;
			}
			else {
				myfile << "usemtl Building" << std::endl;
			}
			myfile << "f " << tiles.at(i).getRightRF(j).a +1<< "/" << tiles.at(i).getRightRF(j).uv1+1 << "/" << tiles.at(i).getRightRF(j).nm + 1<< " " <<
				tiles.at(i).getRightRF(j).b + 1 << "/" << tiles.at(i).getRightRF(j).uv2 + 1 << "/" << tiles.at(i).getRightRF(j).nm + 1<< " " <<
				tiles.at(i).getRightRF(j).c + 1 << "/" << tiles.at(i).getRightRF(j).uv3 + 1<< "/" << tiles.at(i).getRightRF(j).nm + 1 << " " <<
				tiles.at(i).getRightRF(j).d + 1 << "/" << tiles.at(i).getRightRF(j).uv4 + 1<< "/" << tiles.at(i).getRightRF(j).nm + 1 << " " << std::endl;
		}



		for (int j = 0; j < tiles.at(i).getSizeDownRF(); j++) {
			if (downmax && j == tiles.at(i).getSizeDownRF() - 1) {
				myfile << "usemtl new" << std::endl;
			}
			else if (tiles.at(i).height == max && stepByStep && j == tiles.at(i).getSizeDownRF() - 1) {
				myfile << "usemtl new" << std::endl;
			}
			else {
				myfile << "usemtl Building" << std::endl;
			}
			myfile << "f " << tiles.at(i).getDownRF(j).a + 1<< "/" << tiles.at(i).getDownRF(j).uv1 + 1<< "/" << tiles.at(i).getDownRF(j).nm + 1 << " " <<
				tiles.at(i).getDownRF(j).b + 1 << "/" << tiles.at(i).getDownRF(j).uv2 + 1 << "/" << tiles.at(i).getDownRF(j).nm + 1<< " " <<
				tiles.at(i).getDownRF(j).c + 1<< "/" << tiles.at(i).getDownRF(j).uv3 + 1<< "/" << tiles.at(i).getDownRF(j).nm + 1<< " " <<
				tiles.at(i).getDownRF(j).d + 1<< "/" << tiles.at(i).getDownRF(j).uv4 + 1 << "/" << tiles.at(i).getDownRF(j).nm +1  << " " << std::endl;
		}
	}
	myfile.close();
	std::cout << ":::::::::: Writing finished ::::::::::" << std::endl;
}

void Voxelizer::clearMeshInfo()
{
	vertexlist.clear();
	for (int i = 0; i < tiles.size(); i++) {
		tiles.at(i).clearAll();
	}
}



