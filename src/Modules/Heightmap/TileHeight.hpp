#ifndef __TileHeight_HPP__
#define __TileHeight_HPP__

#include "TileType.hpp"

#include <vector>

struct TileHeight
{
    /* data */
    public:
    
    double height;
    TileType type;

    TileHeight();
    TileHeight(int height);
    TileHeight(int height, TileType type);
    

};

#endif