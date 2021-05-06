#ifndef CITYGMLTOOL_HPP
#define CITYGMLTOOL_HPP

#include <iostream>
#include <vector>

#include "DataProfile.hpp"
#include "../Modules/Module.hpp"
#include "../Modules/XMLParser/XMLParser.hpp"
#include "../Modules/GMLtoOBJ/GMLtoOBJ.hpp"
#include "../Modules/Triangulate/CityGMLTriangulate.hpp"
#include "../Modules/Triangulate/Triangle.hpp"
#include "../Modules/Triangulate/tile.hpp"

#include "../Modules/GMLCut/GMLCut.hpp"
#include "../Modules/GMLSplit/GMLSplit.hpp"

#include "../Modules/GMLCut/TextureCityGML.hpp"
#include "../Modules/Voxelizer/Voxelizer.hpp"

class CityGMLTool
{
public:
	CityGMLTool();
	~CityGMLTool();

	Module* findModuleByName(const std::string name);
	void parse(std::string & filename);
	void createOBJ(std::string & gmlFilename, std::string output = "");
	void gmlCut(std::string & gmlFilename, double xmin, double ymin, double xmax, double ymax, bool assignOrCut = true, std::string output = "");
	void gmlSplit(std::string & gmlFilename, int tileX, int tileY, std::string output = "");

	void setFileName(std::string& filename);
	void voxelize(int mapSizeX, int mapSizeY, int horizontalStep, int gridmode, bool material, bool mode);
	void triangulate(std::string& gmlFilename);

private:
	std::vector<Module*> modules;
	CityModel* cityModel;
	std::string filename;

	DataProfile dataProfile = DataProfile::createDataProfileLyon();

};

#endif // !CITYGMLTOOLKIT_HPP

