#include "TileVoxel.hpp"

TileVoxel::TileVoxel(){
    
}

TileVoxel::TileVoxel(int height) {
    this->height = height;
    this->type = Default;
}

TileVoxel::TileVoxel(int height, TileType type){
    this->height = height;
    this->type = type;

}