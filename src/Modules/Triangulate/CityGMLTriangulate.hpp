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
        /**
       *	@brief Retourne la taille de notre liste de Triangle
       *	@param Une liste de triangle
       */

        /**
        *	@brief Build list of triangle from a CityGML building tile
        *	@param
        */
        CityGMLTriangulate(string name);

        /**
        *	@brief Initialise listTriangle
        *	@param CityModel obtenu en parsant le fichier .gml
        */
        void initTriangleList(const citygml::CityModel* cityModel);
        
        /**
        *	@brief Initialise listTrianlge avec un fichier GML
        *	@param gmlFile est le fichier
        */
        void TileTriangleList(std::string& gmlfile);

        /**
        *	@brief Crée un .obj a partir de la liste de triangle
        *	@param Une liste de triangle
        */
        void printBaseTriangleList(TriangleList* triangleList);
        
        /**
        *   @return la taille de listTriangle
        */
        int getTriangleListSize();
        
        /**
        *   @return listTriangle
        */
        TriangleList* getTriangleList();
        
        /**
        *   @return la valeur maximale et minimale de listTriangle (X, Y, Z)
        */
        double getXmin();
        double getXmax();
        double getYmin();
        double getYmax();
        double getZmin();
        double getZmax();

};

#endif // !CITYGMLTRI_HPP