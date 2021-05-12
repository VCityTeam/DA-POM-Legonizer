#ifndef CITYGMLTOOL_HPP
#define CITYGMLTOOL_HPP

#include <iostream>
#include <vector>

#include "DataProfile.hpp"
#include "../Modules/Module.hpp"
#include "../Modules/XMLParser/XMLParser.hpp"

#include "../Modules/Triangulate/CityGMLTriangulate.hpp"
#include "../Modules/Triangulate/Triangle.hpp"
#include "../Modules/Triangulate/tile.hpp"
#include "../Modules/GMLCut/GMLCut.hpp"

#include "../Modules/GMLCut/TextureCityGML.hpp"
#include "../Modules/Voxelizer/Voxelizer.hpp"

class CityGMLTool
{
public:
	CityGMLTool();
	~CityGMLTool();

	Module* findModuleByName(const std::string name);
<<<<<<< HEAD
	void parse(std::string & filename);
	void voxelize(int mapSizeX, int mapSizeY, int horizontalStep, int gridmode, bool material, std::string outPutNameFile, bool debug);
=======
	void voxelize(int mapSizeX, int mapSizeY, int horizontalStep, int gridmode, bool material, std::string& filename);
>>>>>>> 57780e00953dcb4cc6213e82113705c844daf5e7
	void triangulate(std::string& gmlFilename);

private:
	std::vector<Module*> modules;
};

#endif // !CITYGMLTOOLKIT_HPP

