#include "CityGMLTool.hpp"

CityGMLTool::CityGMLTool()
{
	this->modules.push_back(new Voxelizer("voxelizer"));
	this->modules.push_back(new CityGMLTriangulate("triangulate"));
}

CityGMLTool::~CityGMLTool()
{
	//std::cout << "Destructeur CityGMLTool" << std::endl;

	for (int i = 0; i < this->modules.size(); i++)
	{
		delete this->modules[i];
	}

	this->modules.clear();
}

Module* CityGMLTool::findModuleByName(const std::string name)
{
	for (int i = 0; i < this->modules.size(); i++)
	{
		if (this->modules[i]->getName() == name)
		{
			//std::cout << "::[MODULE FOUND]::[NAME=" << this->modules[i].getName() << "]" << std::endl;
			return this->modules[i];
		}
	}
}



void CityGMLTool::voxelize(int mapSizeX, int mapSizeY,int horizontalStep, int gridmode, bool material, std::string inPutFileName, std::string outPutFileName, bool debug) {

	Voxelizer* voxelizer = static_cast<Voxelizer*>(this->findModuleByName("voxelizer"));
	CityGMLTriangulate* triangulate = static_cast<CityGMLTriangulate*>(this->findModuleByName("triangulate"));

	voxelizer->init(mapSizeX, mapSizeY,horizontalStep, gridmode, material, debug);
	triangulate->initTriangleList(inPutFileName);

	
	triangulate->printBaseTriangleList(triangulate->getTriangleList());
	
	/*for (int i = 0; i < triangulate->getTriangleListSize(); i++) {
		std::cout << "triangle " << i << std::endl;
		std::cout << triangulate->getTriangleList()->triangles.at(0)->a<< std::endl;
		std::cout << triangulate->getTriangleList()->triangles.at(0)->b << std::endl;
		std::cout << triangulate->getTriangleList()->triangles.at(0)->c << std::endl;
	}*/


	voxelizer->computeHeightMap(triangulate);
	voxelizer->remesh();
	voxelizer->printObj(outPutFileName);
}


void CityGMLTool::triangulate(std::string& filename) {

	CityGMLTriangulate* cityTriangulate = static_cast<CityGMLTriangulate*>(this->findModuleByName("triangulate"));
	cityTriangulate->initTriangleList(filename);
	cityTriangulate->printBaseTriangleList(cityTriangulate->getTriangleList());
	std::cout << "Object triangulate creer !";	
}	
