#ifndef CITYGMLTRI_HPP
#define CITYGMLTRI_HPP

using namespace std;
#include "../Module.hpp"
#include "../../CityModel/CityModel.hpp"
#include "Triangle.hpp"

class CityGMLTriangulate : public Module {
    
    private:

        TriangleList* listTriangle;

    public:

        CityGMLTriangulate(string name);
        void initTriangleList(const citygml::CityModel* cityModel);
        void TileTriangleList(std::string& gmlfile);
        void printBaseTriangleList(TriangleList* triangleList);
        int getTriangleListSize();
        TriangleList* getTriangleList();
    
        /* Retourne la valeur max et min de la liste de triangle */
        double getXmin();
        double getXmax();
        double getYmin();
        double getYmax();
        double getZmin();
        double getZmax();

};

#endif // !CITYGMLTRI_HPP