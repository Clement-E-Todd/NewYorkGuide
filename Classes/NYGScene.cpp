//
//  NYGScene.cpp
//  New York Guide
//
//  Created by Clément Todd on 2013-12-08.
//  Copyright Clément Todd 2013. All rights reserved.
//

#include "NYGScene.h"
#include "Defines.h"
#include "CompositeSprite.h"
#include "MapNavigator.h"

using namespace cocos2d;

/**
 @brief     Create a CCScene containing a NewYorkGuide layer.
 @return    A pointer to the newly created scene.
 */
CCScene* NewYorkGuide::scene()
{
    CCScene *scene = CCScene::create();
    NewYorkGuide *layer = NewYorkGuide::create();
    scene->addChild(layer);
    return scene;
}

/**
 @brief     Initialize the layer by populating it with its contents.
 @return    true    The layer was initialized successfully.
 @return    false   The layer failed to initialize.
 */
bool NewYorkGuide::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }
    
    // Create a node for the map and add its sprites to it.
    CompositeSprite* map = CompositeSprite::create("map", ".png", 4, 5);
    if (map)
    {
        map->setPosition(WIN_SIZE.width/2, WIN_SIZE.height/2);
    }
    else
    {
        return false;
    }
    
    // Create a map navigator node so the user can move the map around, then add the map to it.
    MapNavigator* navigator = MapNavigator::create(map);
    if (navigator && map)
    {
        addChild(navigator);
        navigator->addChild(map);
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
