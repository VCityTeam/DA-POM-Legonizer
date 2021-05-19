#ifndef __VOXELIZER_HPP__
#define __VOXELIZER_HPP__

#include "../../CityModel/Vecs.hpp"
#include <list>
#include "../Module.hpp"
#include "./TileVoxel.hpp"
#include "../Heightmap/TileType.hpp"
#include "../Triangulate/Triangle.hpp"
#include "../Triangulate/CityGMLTriangulate.hpp"    
#include "Rectangleface.hpp"
#include "../Heightmap/TileHeight.hpp"
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
        void init(int mapSizeX, int mapSizeY, int horizontalStep, int gridmode, bool material, std::vector<TileHeight> tileHeight, bool stepByStep, bool debug);

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
        *   @brief Print all the structure remesh in OBJ
        *   @param Filename.obj
        */
        void clearMeshInfo();

        /*
        *   @brief if true, print the obj step-by-step 
        */
        bool stepByStep;

        /*
        *   @brief max step in step-by-step mode
        */
        double max;

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