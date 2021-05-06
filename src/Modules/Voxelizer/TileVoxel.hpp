#ifndef __Tile_HPP__
#define __Tile_HPP__

#include "TileType.hpp"
#include "Rectangleface.hpp"
#include <vector>

struct TileVoxel
{
    /* data */
    public:
    
    int height;
    TileType type;
    Rectangleface top;
    std::vector<Rectangleface> right;
    std::vector<Rectangleface> down;

    TileVoxel();
    TileVoxel(int height);
    TileVoxel(int height, TileType type);
    
    void pushRectangleFaceRight(Rectangleface rect) { right.push_back(rect); }

    void pushRectangleFaceDown(Rectangleface rect) { down.push_back(rect); }

    int getSizeRightRF() { return right.size(); }

    int getSizeDownRF() { return down.size(); }

    Rectangleface getRightRF(int i) { return right.at(i); }

    Rectangleface getDownRF(int i) { return down.at(i); }
};

#endif