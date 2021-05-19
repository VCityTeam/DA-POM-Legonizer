#include "TileHeight.hpp"

TileHeight::TileHeight(){
    
}

TileHeight::TileHeight(int height) {
    this->height = height;
    this->type = Ground;
}

TileHeight::TileHeight(int height, TileType type){
    this->height = height;
    this->type = type;

}