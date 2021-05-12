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

void CityGMLTool::voxelize(int mapSizeX, int mapSizeY,int horizontalStep, int gridmode, bool material, std::string& filename) {
	Voxelizer* voxelizer = static_cast<Voxelizer*>(this->findModuleByName("voxelizer"));
	CityGMLTriangulate* triangulate = static_cast<CityGMLTriangulate*>(this->findModuleByName("triangulate"));

	voxelizer->init(mapSizeX, mapSizeY,horizontalStep, gridmode, material);
	triangulate->initTriangleList(filename);
	//triangulate->initTriangleList(cityModel);
	
	triangulate->printBaseTriangleList(triangulate->getTriangleList());
	
	/*for (int i = 0; i < triangulate->getTriangleListSize(); i++) {
		std::cout << "triangle " << i << std::endl;
		std::cout << triangulate->getTriangleList()->triangles.at(0)->a<< std::endl;
		std::cout << triangulate->getTriangleList()->triangles.at(0)->b << std::endl;
		std::cout << triangulate->getTriangleList()->triangles.at(0)->c << std::endl;
	}*/

	std::cout << "liste triangles termines" << std::endl;
	voxelizer->compute(triangulate);
	//appel du module triangle
}


void CityGMLTool::triangulate(std::string& filename) {

	CityGMLTriangulate* cityTriangulate = static_cast<CityGMLTriangulate*>(this->findModuleByName("triangulate"));
	cityTriangulate->initTriangleList(filename);
	cityTriangulate->printBaseTriangleList(cityTriangulate->getTriangleList());
	std::cout << "Object triangulate creer !";	
}	
