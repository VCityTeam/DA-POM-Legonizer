#include "TileVoxel.hpp"

TileVoxel::TileVoxel(){
    
}

TileVoxel::TileVoxel(int height) {
    this->height = height;
    this->type = Ground;
}

TileVoxel::TileVoxel(int height, TileType type){
    this->height = height;
    this->type = type;

}