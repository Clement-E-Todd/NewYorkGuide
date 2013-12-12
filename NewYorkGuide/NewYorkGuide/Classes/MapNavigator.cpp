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
    // If we aren't already tracking 2 touches, track this one. Otherwise ignore this touch.
    unsigned char touchID;
    if (!m_Touches[0])
    {
        m_Touches[0] = pTouch;
        touchID = 0;
    }
    else if (!m_Touches[1])
    {
        m_Touches[1] = pTouch;
        touchID = 1;
    }
    else
    {
        return false;
    }
    
    // If we are only tracking one touch, set up for panning logic.
    if ((m_Touches[0] && !m_Touches[1]) || (!m_Touches[0] && m_Touches[1]))
    {
        m_MapNodeStartPosition = m_MapNode->getPosition();
        m_TouchStartPositions[touchID] = m_Touches[touchID]->getLocation();
    }
    
    // If we are tracking two touches, set up for zooming logic.
    else if (m_Touches[0] && m_Touches[1])
    {
        m_MapNodeStartPosition = m_MapNode->getPosition();
        m_MapNodeStartScale = m_MapNode->getScale();
        m_TouchStartPositions[0] = m_Touches[0]->getLocation();
        m_TouchStartPositions[1] = m_Touches[1]->getLocation();
    }
    
    return true;
}

/**
 @brief     Respond to the user's continued touch input.
 @param     pTouch      A pointer to the touch information.
 @param     pEvent      The event data.
 */
void MapNavigator::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    // If we are only tracking one touch then pan the map based on the touch position.
    if ((m_Touches[0] && !m_Touches[1]) || (!m_Touches[0] && m_Touches[1]))
    {
        unsigned char touchID = m_Touches[0] ? 0 : 1;
        m_MapNode->setPosition(ccpAdd(m_MapNodeStartPosition, ccpSub(m_Touches[touchID]->getLocation(), m_TouchStartPositions[touchID])));
    }
    
    // If we are tracking two touches, zoom in or out based on their positions relative to each other.
    else if (m_Touches[0] && m_Touches[1])
    {
        // Compare the original distance between the two touches and their original distance to find out how far zoomed in / out we should be.
        float originalDistance = ccpDistance(m_TouchStartPositions[0], m_TouchStartPositions[1]);
        float currentDistance = ccpDistance(m_Touches[0]->getLocation(), m_Touches[1]->getLocation());
        float scaleFactor = currentDistance / originalDistance;
        
        // Scale the map based on the value we just calculated.
        m_MapNode->setScale(m_MapNodeStartScale * scaleFactor);
        
        // Also pan the view based on the midpoint of the two touches.
        CCPoint originalMidpoint = ccpMidpoint(m_TouchStartPositions[0], m_TouchStartPositions[1]);
        CCPoint currentMidpoint = ccpMidpoint(m_Touches[0]->getLocation(), m_Touches[1]->getLocation());
        m_MapNode->setPosition(ccpAdd(m_MapNodeStartPosition, ccpSub(currentMidpoint, originalMidpoint)));
    }
}

/**
 @brief     Respond to the end of a user's touch.
 @param     pTouch      A pointer to the touch information.
 @param     pEvent      The event data.
 */
void MapNavigator::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    // Clear this touch from our tracked touches.
    if (pTouch == m_Touches[0])
    {
        m_Touches[0] = NULL;
    }
    else if (pTouch == m_Touches[1])
    {
        m_Touches[1] = NULL;
    }
    
    // If we are still tracking another touch, set up for panning logic.
    if ((m_Touches[0] && !m_Touches[1]) || (!m_Touches[0] && m_Touches[1]))
    {
        unsigned char touchID = m_Touches[0] ? 0 : 1;
        m_MapNodeStartPosition = m_MapNode->getPosition();
        m_TouchStartPositions[touchID] = m_Touches[touchID]->getLocation();
    }
}

/**
 @brief     Respond to a user's touch input being lost.
 @param     pTouch      A pointer to the touch information.
 @param     pEvent      The event data.
 */
void MapNavigator::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    ccTouchEnded(pTouch, pEvent);
}
