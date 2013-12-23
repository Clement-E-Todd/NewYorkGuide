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

/**
 @brief     An extension of the Map class specifically set up to display information on Manhattan.
 */
class NewYorkMap : public Map
{
public:
    
    /**
     @brief     Create a NewYorkMap instance.
     @return    A pointer to the newly created NewYorkMap.
     */
    static NewYorkMap* create();
    
protected:
    
    /**
     @brief     Initialize this NewYorkMap instance.
     @return    Whether or not initialization succeeded.
     */
    bool init();
};

#endif // NEW_YORK_MAP_H
