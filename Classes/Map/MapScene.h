//
//  MapScene.h
//  New York Guide
//
//  Created by Clément Todd on 2013-12-08.
//  Copyright Clément Todd 2013. All rights reserved.
//

#ifndef MAP_SCENE_H
#define MAP_SCENE_H

#include "cocos2d.h"

/**
 @brief    The layer in which the application displays itself to the user.
 */
class MapScene : public cocos2d::CCLayer
{
public:
    
    /**
     @brief     Create a CCScene containing a MapScene layer.
     @return    A pointer to the newly created scene.
     */
    static cocos2d::CCScene* scene();
    
    
protected:
    
    /**
     @brief     Create an instance of the MapScene layer.
     @return    A pointer to the newly created layer.
     */
    CREATE_FUNC(MapScene);
    
    /**
     @brief     Initialize the layer by populating it with its contents.
     @return    true    The layer was initialized successfully.
     @return    false   The layer failed to initialize.
     */
    virtual bool init();
};

#endif // MAP_SCENE_H
