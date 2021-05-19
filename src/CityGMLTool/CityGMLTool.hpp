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

#include "../Modules/Voxelizer/Voxelizer.hpp"
#include "../Modules/Heightmap/Heightmap.hpp"

class CityGMLTool
{
public:
	CityGMLTool();
	~CityGMLTool();

	Module* findModuleByName(const std::string name);

	void voxelize(int mapSizeX, int mapSizeY, int horizontalStep, int gridmode, bool material, bool stepByStep, std::string inputFileName, std::string outPutNameFile, std::string fileNameCSV, bool debug);
	void heightmap(int mapSizeX, int mapSizeY, int horizontalStep, std::string inPutFileName, std::string fileNameCSV, bool debug);
	void triangulate(std::string& gmlFilename, bool debug);

private:
	std::vector<Module*> modules;
};

#endif // !CITYGMLTOOLKIT_HPP

