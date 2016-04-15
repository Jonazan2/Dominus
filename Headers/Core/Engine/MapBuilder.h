#ifndef __Dominus_MapBuilder_h__
#define __Dominus_MapBuilder_h__

#include "Map.h"
#include "MapLoader.h"
#include "TilesLoader.h"
#include "ObjLoader.h"

class MapBuilder {
public:
    MapBuilder();
    ~MapBuilder();

    std::shared_ptr<Map> build( MapLoader* mapLoader, TilesLoader* tilesLoader );
};

#endif /* _MAP_BUILDER_H_ */
