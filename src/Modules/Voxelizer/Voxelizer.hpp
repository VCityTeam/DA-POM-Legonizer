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
struct Voxelizer : public Module
{
    /* data */
    public:
        Voxelizer(std::string name);

        /*
        * Initialise les variables
        */
        void init(int mapSizeX, int mapSizeY, int horizontalStep, int gridmode, bool material, bool mode);

        /* 
        * Lancer de rayons et constitution de la heightmap
        */
        void compute(CityGMLTriangulate* cityGMLTriangulate);

        /*
        * Refait le maillage a partir de la heightmap
        */
        void rectangulize();

        /*
        * Transforme les données en un fichier .obj
        */
        void printObj();

        /*
        *
        */
        void printvertices();

        /*
        * Taille de la map en pixel
        */
        TVec2<int> mapsize;

        /*
        * Heightmap
        */
        std::vector<TileVoxel> tiles;

        /*
        * Liste des vertex
        */
        std::vector<TVec3d> vertexlist;

        /*
        * Liste des UV
        */
        std::vector<UV> uvlist;

        /*
        * Liste des normales
        */
        std::vector<Normales> normalelist;
        

        /*
        * Hauteur maximale des lancés de rayons
        */
        int maxHeight = 255;

        /*
        * Hauteur du sol
        */
        int minHeight = 0;

        /*
        * Dimensions de la taille des cases de la grille 
        */
        int scale = 1;

        /*
        * Nombre de pas entre la hauteur maximale et minimale
        */
        int horizontalStep = 250;

        int sizeStep ;

        int gridmode;

        bool material = false;

        bool optimisationRam = false;

        double offsetX;

        double offsetY;


};

#endif