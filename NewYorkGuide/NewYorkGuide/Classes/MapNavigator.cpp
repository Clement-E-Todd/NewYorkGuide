//
//  MapNavigator.cpp
//  NewYorkGuide
//
//  Created by Clement Todd on 2013-12-11.
//
//

#include "MapNavigator.h"

using namespace cocos2d;

/**
 @brief     Create an MapNavigator instance with a target map node.
 @param     mapNode     The map which should be manipulated by the navigator.
 @return    A pointer to the newly created MapNavigator.
 */
MapNavigator* MapNavigator::create(CCNode* mapNode)
{
    MapNavigator *mapNavigator = new MapNavigator();
    if (mapNavigator && mapNavigator->init(mapNode))
    {
        mapNavigator->autorelease();
        return mapNavigator;
    }
    CC_SAFE_DELETE(mapNavigator);
    return NULL;
}

/**
 @brief     Initialize the map navigator with its target map node.
 @param     mapNode     The map which should be manipulated by the navigator.
 @return    Whether or not the initialization was successful.
 */
bool MapNavigator::init(CCNode *mapNode)
{
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
    
    m_MapNode = mapNode;
    return m_MapNode;
}

/**
 @brief     Called when the map navigator is removed from the node tree.
 */
void MapNavigator::onExit()
{
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    CCNode::onExit();
}

/**
 @brief     Respond to the beginning of a user's touch.
 @param     pTouch      A pointer to the touch information.
 @param     pEvent      The event data.
 @return    Whether or not the map navigator accepted the touch input.
 */
bool MapNavigator::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    m_MapNodeStartPosition = m_MapNode->getPosition();
    m_TouchStartPosition = pTouch->getLocation();
    return true;
}

/**
 @brief     Respond to the user's continued touch input.
 @param     pTouch      A pointer to the touch information.
 @param     pEvent      The event data.
 */
void MapNavigator::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    m_MapNode->setPosition(ccpAdd(m_MapNodeStartPosition, ccpSub(pTouch->getLocation(), m_TouchStartPosition)));
}
