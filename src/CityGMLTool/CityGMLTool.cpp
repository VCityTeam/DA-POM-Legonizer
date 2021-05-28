#include "CityGMLTool.hpp"

CityGMLTool::CityGMLTool()
{
	this->modules.push_back(new Voxelizer("voxelizer"));
	this->modules.push_back(new CityGMLTriangulate("triangulate"));
	this->modules.push_back(new Heightmap("heightmap"));
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
	return this->modules[0];
}



void CityGMLTool::voxelize(int mapSizeX, int mapSizeY,int horizontalStep, int gridmode, bool material, bool stepByStep, std::string inPutFileName, std::string outPutFileName, std::string fileNameCSV, bool debug) {
	Heightmap* heightmap = static_cast<Heightmap*>(this->findModuleByName("heightmap"));
	Voxelizer* voxelizer = static_cast<Voxelizer*>(this->findModuleByName("voxelizer"));
	CityGMLTriangulate* triangulate = static_cast<CityGMLTriangulate*>(this->findModuleByName("triangulate"));
	
	
	triangulate->initTriangleList(inPutFileName, debug);

	triangulate->printBaseTriangleList(triangulate->getTriangleList());
	
	heightmap->init(mapSizeX, mapSizeY, horizontalStep, debug);
	heightmap->computeHeightMap(triangulate);
	heightmap->printHeightMap2(fileNameCSV);

	
	voxelizer->init(mapSizeX, mapSizeY, horizontalStep, gridmode, material, heightmap->tiles, stepByStep, debug );
	voxelizer->sizeStep = heightmap->sizeStep;
	voxelizer->sizeStepX = heightmap->sizeStepY;
	voxelizer->sizeStepY = heightmap->sizeStepX;
	if (stepByStep) {
		for (int i = horizontalStep; i >= 0; i--) {

			voxelizer->remesh();
			voxelizer->printObj(outPutFileName + std::to_string(i + 1) + ".obj");
			voxelizer->clearMeshInfo();
			for (int j = 0; j < voxelizer->tiles.size(); j++) {

				if (voxelizer->tiles.at(j).height > i * voxelizer->sizeStep) {
					voxelizer->tiles.at(j).height = i * voxelizer->sizeStep;

				}
				voxelizer->max = i * voxelizer->sizeStep;
			}
		}
	}
	else {
		voxelizer->remesh();
		voxelizer->printObj(outPutFileName + ".obj");
		voxelizer->clearMeshInfo();
	}
}

void CityGMLTool::heightmap(int mapSizeX, int mapSizeY, int horizontalStep, std::string inPutFileName, std::string fileNameCSV, bool debug)
{
	Heightmap* heightmap = static_cast<Heightmap*>(this->findModuleByName("heightmap"));
	CityGMLTriangulate* triangulate = static_cast<CityGMLTriangulate*>(this->findModuleByName("triangulate"));

	heightmap->init(mapSizeX, mapSizeY, horizontalStep, debug);
	heightmap->computeHeightMap(triangulate);
	heightmap->printHeightMap2(fileNameCSV);


}


void CityGMLTool::triangulate(std::string& filename, bool debug) {

	CityGMLTriangulate* cityTriangulate = static_cast<CityGMLTriangulate*>(this->findModuleByName("triangulate"));
	cityTriangulate->initTriangleList(filename, debug);
	cityTriangulate->printBaseTriangleList(cityTriangulate->getTriangleList());
	std::cout << ":::::::::: Object triangulate create ::::::::::";	
}	
