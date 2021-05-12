#ifndef __VOXELIZER_HPP__
#define __VOXELIZER_HPP__

#include "../../CityModel/Vecs.hpp"
#include <list>
#include "../Module.hpp"
#include "./TileVoxel.hpp"
#include "./TileType.hpp"
#include "../Triangulate/Triangle.hpp"
#include "../Triangulate/CityGMLTriangulate.hpp"    
#include "Rectangleface.hpp"

/*
* @brief Voxelizing a GML file using raytracing from OSG
*/
struct Voxelizer : public Module
{
    /* data */
    public:
        Voxelizer(std::string name);

        /**
       *	@brief Initialize the settings
       *	@param Number of rays in X axis
       *    @param Number of rays in Y axis
       *    @param Number of step on Z axis
       *    @param Mode of re mesh (0 = one face between all height, 1 = vertical faces are cutted in stepSize)
       *    @param if true : enable material 
       */
        void init(int mapSizeX, int mapSizeY, int horizontalStep, int gridmode, bool material, bool debug);

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

        /*
        *   @brief Remesh with the heightmap
        */
        void remesh();

        /*
        *   @brief Print all the structure remesh in OBJ
        *   @param Filename.obj
        */
        void printObj(const std::string);

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
        std::vector<TileVoxel> tiles;

        /*
        * @brief List of all remeshed vertices
        */
        std::vector<TVec3d> vertexlist;

        /*
        * @brief List of all remeshed uv
        */
        std::vector<UV> uvlist;

        /*
        * @brief List of all remeshed normales
        */
        std::vector<Normales> normalelist;

        /*
        * @brief Number of step between the Zmin and Zmax
        */
        int horizontalStep = 250;

        /*
        * @brief Size of Z step
        */
        double sizeStep;

        /*
        * @brief Mode of re mesh (0 = one face between all height, 1 = vertical faces are cutted in stepSize) 
        */
        int gridmode;

        /*
        * @brief if true, material is enabled (one for the ground and one for the the building
        */
        bool material = false;

};

#endif