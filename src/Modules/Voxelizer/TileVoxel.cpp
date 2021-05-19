#include "TileVoxel.hpp"

TileVoxel::TileVoxel(){
    
}

TileVoxel::TileVoxel(double height) {
    this->height = height;
    this->type = Ground;
}

TileVoxel::TileVoxel(double height, TileType type){
    this->height = height;
    this->type = type;

}

void TileVoxel::clearAll()
{
    right.clear();
    down.clear();
}
