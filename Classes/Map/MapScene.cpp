//
//  MapScene.cpp
//  New York Guide
//
//  Created by Clément Todd on 2013-12-08.
//  Copyright Clément Todd 2013. All rights reserved.
//

#include "MapScene.h"
#include "Defines.h"
#include "CompositeSprite.h"
#include "Map.h"

using namespace cocos2d;

/**
 @brief     Create a CCScene containing a MapScene layer.
 @return    A pointer to the newly created scene.
 */
CCScene* MapScene::scene()
{
    CCScene *scene = CCScene::create();
    MapScene *layer = MapScene::create();
    scene->addChild(layer);
    return scene;
}

/**
 @brief     Initialize the layer by populating it with its contents.
 @return    true    The layer was initialized successfully.
 @return    false   The layer failed to initialize.
 */
bool MapScene::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    // Create a map for the user to navigate.
    Map* map = Map::create(CompositeSprite::create("map", ".png", 4, 5));
    if (map)
    {
        addChild(map);
        map->setPosition(ccp(WIN_SIZE.width/2, WIN_SIZE.height/2));
    }
    else
    {
        return false;
    }
    
    // TEMP
    CCSprite* sprite = CCSprite::create("infoButton.png");
    addChild(sprite);
    sprite->setPosition(ccp(WIN_SIZE.width/2, WIN_SIZE.height/2));
    
    return true;
}
