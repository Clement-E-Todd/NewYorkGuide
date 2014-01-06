//
//  NewYorkMap.h
//  NewYorkGuide
//
//  Created by Clement Todd on 2013-12-22.
//
//

#ifndef NEW_YORK_MAP_H
#define NEW_YORK_MAP_H

#include "Map.h"
#include "CompositeSprite.h"

/**
 @brief     An extension of the Map class specifically set up to display information on Manhattan.
 */
class NewYorkMap : public Map, public CompositeSpriteObserver
{
public:
    
    /**
     @brief     Create a NewYorkMap instance.
     @return    A pointer to the newly created NewYorkMap.
     */
    static NewYorkMap* create();
    
    /**
     @brief     Reaction to the end of a CompositeSprite's loading cycle.
     */
    void compositeSpriteFinishedLoading(CompositeSprite* sprite);
    
protected:
    
    /**
     @brief     Initialize this NewYorkMap instance.
     @return    Whether or not initialization succeeded.
     */
    bool init();
    
    /**
     @brief     Begin loading the map. Called after a delay to allow the loading popup to be added to the main scene.
     */
    void loadMap();
    
};

#endif // NEW_YORK_MAP_H
