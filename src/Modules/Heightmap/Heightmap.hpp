#ifndef __HEIGHTMAP_HPP__
#define __HEIGHTMAP_HPP__

#include "../../CityModel/Vecs.hpp"
#include <list>
#include "../Module.hpp"
#include "./TileHeight.hpp"
#include "./TileType.hpp"
#include "../Triangulate/Triangle.hpp"
#include "../Triangulate/CityGMLTriangulate.hpp"    


/*
* @brief Voxelizing a GML file using raytracing from OSG
*/
struct Heightmap : public Module
{
    /* data */
    public:
        Heightmap(std::string name);

        /**
       *	@brief Initialize the settings
       *	@param Number of rays in X axis
       *    @param Number of rays in Y axis
       *    @param Number of step on Z axis
       *    @param Mode of re mesh (0 = one face between all height, 1 = vertical faces are cutted in stepSize)
       *    @param if true : enable material 
       */
        void init(int mapSizeX, int mapSizeY, int horizontalStep, bool debug);

        /**
       *	@brief Launch rayTracing and providing the heightmap
       *	@param objectTriangleList
       */
        void computeHeightMap(CityGMLTriangulate* cityGMLTriangulate);

        /**
        *	@brief Print heigtMap in CSV
        *	@param Filename.csv
        */
        void printHeightMap(const std::string);

        /**
        *	@brief Print heigtMap in CSV round for minecraft
        *	@param Filename.csv
        */
        void printHeightMap2(const std::string);

        /*
        *   @brief if true, enable debugging
        */
        bool debug;

        /*
        * @brief size of Heightmap in [x,y]
        */
        TVec2<int> mapsize;

        /*
        * @brief Heightmap
        */
        std::vector<TileHeight> tiles;

        /*
        * @brief Number of step between the Zmin and Zmax
        */
        int horizontalStep = 250;

        /*
        * @brief Size of Z step
        */
        double sizeStep;

        /*
        * @brief longueur d'une case en X
        */
        double sizeStepX;

        /*
        * @brief longueur d'une case en Y
        */
        double sizeStepY;


};

#endif