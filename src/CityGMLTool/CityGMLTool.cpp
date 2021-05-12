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

<<<<<<< HEAD
void CityGMLTool::parse(std::string & filename)
{	
	XMLParser* xmlparser = static_cast<XMLParser*>(this->findModuleByName("xmlparser"));

	citygml::ParserParams params = citygml::ParserParams();
	cityModel = xmlparser->load(filename, params);

	// == 0 if the parsing failed, file name/location may be wrong
	if (cityModel == 0)
	{
		std::cout << "PARSING:.............................:[FAILED]" << std::endl;
		exit(1);
		return;
	}

	std::cout << "PARSING:.............................:[OK]" << std::endl;

	/*
		==============================================
		::::::::::::::::: DEBUG PART :::::::::::::::::
		==============================================
	*/

	//std::cout << "city objects roots - size : " << cityModel->getCityObjectsRoots().size() << std::endl;
	//for (int i = 0; i < cityModel->getCityObjectsRoots().size(); i++)
	//{
	//	std::cout << (cityModel->getCityObjectsRoots()[i]->getTypeAsString()) << " ";
	//	std::cout << cityModel->getCityObjectsRoots()[i]->getChildCount() << " children ";
	//	std::cout << cityModel->getCityObjectsRoots()[i]->getGeometries().size() << " geometries" << std::endl;

	//	// If CityObject type is "Bridge", they have no children so we don't need to go deeper
	//	if (cityModel->getCityObjectsRoots()[i]->getType() == CityObjectsType::COT_Bridge) {
	//		for (int geo = 0; geo < cityModel->getCityObjectsRoots()[i]->getGeometries().size(); geo++) {

	//			const Geometry* geometry = cityModel->getCityObjectsRoots()[i]->getGeometry(geo);
	//			std::cout << "\t " << *geometry << std::endl;
	//		}
	//	}
	//	// If CityObject type is "Building", we need to go deeper
	//	else if (cityModel->getCityObjectsRoots()[i]->getType() == CityObjectsType::COT_Building) {
	//		for (int j = 0; j < cityModel->getCityObjectsRoots()[i]->getChildCount(); j++)
	//		{
	//			const CityObject* obj = cityModel->getCityObjectsRoots()[i]->getChild(j);

	//			std::cout << "\t" << (obj->getTypeAsString()) << " - ";
	//			std::cout << obj->getChildCount() << " children ";
	//			std::cout << obj->getGeometries().size() << " geometries" << std::endl;

	//			// If CityObject type is "BuildingPart", we need to go deeper
	//			if (obj->getType() == CityObjectsType::COT_BuildingPart) {
	//				for (int k = 0; k < obj->getChildren().size(); k++) {
	//					std::cout << "\t\t" << obj->getChild(k)->getTypeAsString() << " - ";
	//					std::cout << obj->getChild(k)->getChildCount() << " children ";
	//					std::cout << obj->getChild(k)->getGeometries().size() << " geometries" << std::endl;
	//				}
	//			}
	//		}
	//	}
	//}
}

void CityGMLTool::voxelize(int mapSizeX, int mapSizeY,int horizontalStep, int gridmode, bool material, std::string outPutFileName, bool debug) {

	Voxelizer* voxelizer = static_cast<Voxelizer*>(this->findModuleByName("voxelizer"));
	CityGMLTriangulate* triangulate = static_cast<CityGMLTriangulate*>(this->findModuleByName("triangulate"));

	voxelizer->init(mapSizeX, mapSizeY,horizontalStep, gridmode, material, debug);
	triangulate->initTriangleList(cityModel);
=======
void CityGMLTool::voxelize(int mapSizeX, int mapSizeY,int horizontalStep, int gridmode, bool material, std::string& filename) {
	Voxelizer* voxelizer = static_cast<Voxelizer*>(this->findModuleByName("voxelizer"));
	CityGMLTriangulate* triangulate = static_cast<CityGMLTriangulate*>(this->findModuleByName("triangulate"));

	voxelizer->init(mapSizeX, mapSizeY,horizontalStep, gridmode, material);
	triangulate->initTriangleList(filename);
	//triangulate->initTriangleList(cityModel);
>>>>>>> 57780e00953dcb4cc6213e82113705c844daf5e7
	
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
