#include "MapBuilder.h"

MapBuilder::MapBuilder() {

}

std::shared_ptr<Map> MapBuilder::build( MapLoader *mapLoader,
                                        TilesLoader *tilesLoader ) {
    std::shared_ptr<Map> map( new Map );
    
    MapInfo* mapInfo = mapLoader->load();
    std::vector<std::string> tilesInfo = tilesLoader->load( mapInfo->tilesResource );
    
    for ( int i = 0 ; i < mapInfo->tilesKeys.size(); i++ ) {
        int tileKey = mapInfo->tilesKeys.at( i );
        std::shared_ptr<Mesh> mesh =
            std::shared_ptr<Mesh>( new Mesh( make_unique< ObjLoader >() ) );
        mesh->load( tilesInfo.at( tileKey ) );
        
        std::shared_ptr<Tile> tile( new Tile );
        tile->key = tileKey;
        tile->setMesh( mesh );
        
        map->addTile( tile );
    }
    map->columns = mapInfo->width;
    map->rows = mapInfo->height;
    return map;
}

MapBuilder::~MapBuilder() {
    
}