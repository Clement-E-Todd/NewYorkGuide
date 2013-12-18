//
//  Map.cpp
//  NewYorkGuide
//
//  Created by Clement Todd on 2013-12-11.
//
//

#include "Map.h"
#include "Defines.h"

using namespace cocos2d;

#define MIN_SCALE   ((WIN_SIZE.width / getContentSize().width) * 2)
#define MAX_SCALE   (1.5f)

/**
 @brief     Create a Map instance with a target map node.
 @param     mapNode     The node which visually represents the map.
 @return    A pointer to the newly created Map.
 */
Map* Map::create(CCNode* mapNode)
{
    Map *map = new Map();
    if (map && map->init(mapNode))
    {
        map->autorelease();
        return map;
    }
    CC_SAFE_DELETE(map);
    return NULL;
}

/**
 @brief     Initialize the map with its target map node.
 @param     mapNode     The node which visually represents the map.
 @return    Whether or not the initialization was successful.
 */
bool Map::init(CCNode *mapNode)
{
    // Listen for touch events.
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
    
    // Register and add the map node
    m_MapNode = mapNode;
    addChild(m_MapNode);
    
    // Set the default spacial information for both the map and map node
    setContentSize(m_MapNode->getContentSize());
    setAnchorPoint(m_MapNode->getAnchorPoint());
    m_MapNode->setPosition(ccp(getContentSize().width * getAnchorPoint().x, getContentSize().height * getAnchorPoint().y));
    setScale((MIN_SCALE + MAX_SCALE) / 2);
    
    return m_MapNode;
}

/**
 @brief     Respond to the beginning of a user's touch.
 @param     pTouch      A pointer to the touch information.
 @param     pEvent      The event data.
 @return    Whether or not the map accepted the touch input.
 */
bool Map::ccTouchBegan(CCTouch *pTouch, CCEvent *pEvent)
{
    // If we aren't already tracking 2 touches, track this one. Otherwise ignore this touch.
    if (!m_Touches[0])
    {
        m_Touches[0] = pTouch;
    }
    else if (!m_Touches[1])
    {
        m_Touches[1] = pTouch;
    }
    else
    {
        return false;
    }
    
    // Cancel any CCActions currently being run to give the appearance that the user's finger is holding the map still.
    stopAllActions();
    
    // If we are only tracking one touch, set up for panning logic.
    if (setUpForPanning())
    {
        if (DISPLAY_TOUCH_MESSAGES)
        {
            CCLOG("New touch detected and being used for panning.");
        }
    }
    
    // If we are tracking two touches, set up for zooming logic.
    else if (setUpForZooming())
    {
        if (DISPLAY_TOUCH_MESSAGES)
        {
            CCLOG("New touch detected and being used for zooming in combination with the previous touch.");
        }
    }
    
    return true;
}

/**
 @brief     Respond to the user's continued touch input.
 @param     pTouch      A pointer to the touch information.
 @param     pEvent      The event data.
 */
void Map::ccTouchMoved(CCTouch *pTouch, CCEvent *pEvent)
{
    // If we are only tracking one touch then pan the map based on the touch position.
    if ((m_Touches[0] && !m_Touches[1]) || (!m_Touches[0] && m_Touches[1]))
    {
        // Move the map to its new position.
        unsigned char touchID = m_Touches[0] ? 0 : 1;
        setPosition(ccpAdd(m_MapNodeStartPosition, ccpSub(m_Touches[touchID]->getLocation(), m_TouchStartPositions[touchID])));
        
        // Apply limits to the map's position.
        applyTransformLimitationsToMap();
    }
    
    // If we are tracking two touches, zoom in or out based on their positions relative to each other.
    else if (m_Touches[0] && m_Touches[1])
    {
        // Compare the original distance between the two touches and their original distance to find out how far zoomed in / out we should be.
        float originalDistance = ccpDistance(m_TouchStartPositions[0], m_TouchStartPositions[1]);
        float currentDistance = ccpDistance(m_Touches[0]->getLocation(), m_Touches[1]->getLocation());
        float scaleFactor = currentDistance / originalDistance;
        
        // Scale the map based on the value we just calculated.
        setScale(m_MapNodeStartScale * scaleFactor);
        
        // Also pan the view based on the midpoint of the two touches.
        CCPoint originalMidpoint = ccpMidpoint(m_TouchStartPositions[0], m_TouchStartPositions[1]);
        CCPoint currentMidpoint = ccpMidpoint(m_Touches[0]->getLocation(), m_Touches[1]->getLocation());
        setPosition(ccpAdd(m_MapNodeStartPosition, ccpSub(currentMidpoint, originalMidpoint)));
        
        // Apply limits to the map's position and scale.
        applyTransformLimitationsToMap();
    }
}

/**
 @brief     Respond to the end of a user's touch.
 @param     pTouch      A pointer to the touch information.
 @param     pEvent      The event data.
 */
void Map::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
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
    
    // In the event that we are still tracking another touch, set up to use it for panning.
    if (setUpForPanning())
    {
        if (DISPLAY_TOUCH_MESSAGES)
        {
            CCLOG("A touch ended, and the remaining touch is now being used for panning.");
        }
    }
    
    // If all tracked touches have now ended, check the map's transform and snap it back into place if need be.
    else
    {
        snapMapToTransformLimitations();
        
        if (DISPLAY_TOUCH_MESSAGES)
        {
            CCLOG("All recorded touches have ended.");
        }
    }
}

/**
 @brief     Respond to a user's touch input being lost.
 @param     pTouch      A pointer to the touch information.
 @param     pEvent      The event data.
 */
void Map::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    // End the lost touch the same way we would normally end a touch.
    ccTouchEnded(pTouch, pEvent);
}

/**
 @brief     Record any necessary information in anticipation of panning.
 @return    Whether or not the conditions for panning were met; this method will only succeed if we are tracking exactly one touch.
 */
bool Map::setUpForPanning()
{
    // We must be tracking one and only one touch for this method to succeed, so return immediately otherwise.
    if ((m_Touches[0] && m_Touches[1]) || (!m_Touches[0] && !m_Touches[1]))
    {
        return false;
    }
    
    // Record all information required for the panning logic.
    unsigned char touchID = m_Touches[0] ? 0 : 1;
    m_MapNodeStartPosition = getPosition();
    m_TouchStartPositions[touchID] = m_Touches[touchID]->getLocation();
    
    return true;
}

/**
 @brief     Record any necessary information in anticipation of zooming.
 @return    Whether or not the conditions for zooming were met; this method will only succeed if we are tracking two touches.
 */
bool Map::setUpForZooming()
{
    // We must be tracking two touches for this method to succeed, so return immediately otherwise.
    if (!m_Touches[0] || !m_Touches[1])
    {
        return false;
    }
    
    // Move the anchor point of the map directly between the user's fingers so that zooming occurs in and out of that point.
    CCPoint oldAnchorPoint = getAnchorPoint();
    setAnchorPoint(getAnchorPointFromLocation(ccpMidpoint(m_Touches[0]->getLocation(), m_Touches[1]->getLocation())));
    
    // Adjust the position of the map to avoid an awkward jerk after changing the anchor point.
    setPosition(ccpAdd(getPosition(),
                                  ccpSub(ccp(getContentSize().width * getScale() * getAnchorPoint().x,
                                             getContentSize().height * getScale() * getAnchorPoint().y),
                                         ccp(getContentSize().width * getScale() * oldAnchorPoint.x,
                                             getContentSize().height * getScale() * oldAnchorPoint.y))));
    
    // Record all information required for the zooming logic.
    m_MapNodeStartPosition = getPosition();
    m_MapNodeStartScale = getScale();
    m_TouchStartPositions[0] = m_Touches[0]->getLocation();
    m_TouchStartPositions[1] = m_Touches[1]->getLocation();
    
    return true;
}

/**
 @brief     Translate a point on-screen (for example, a touch location) into an anchor point for the map node.
 @param     location    The on-screen position to be translated.
 @return    The resulting anchor point.
 */
CCPoint Map::getAnchorPointFromLocation(CCPoint location)
{
    CCPoint anchorPoint = convertToNodeSpace(location);
    anchorPoint = ccp(anchorPoint.x / getContentSize().width, anchorPoint.y / getContentSize().height);
    return anchorPoint;
}

/**
 @brief     Keep the map from going too far outside of its positional and scaling limitations.
 */
void Map::applyTransformLimitationsToMap()
{
    /*
     Here we will be preventing the map's transform from going too far outside of their reasonable boundaries
     by first checking the transform and then pulling it back within its limits. However, we don't want to
     pull it *all* the way back, because that gives a jarring and unpleasant feeling to the user experience.
     We instead create an "elastic" effect by dividing the amount we are pulling the transformation back by
     a constant "elasticity" value, as defined below.
     */
    const float elasticity = 1.4f;
    
    // Keep the map's position on-screen, checking each side one at a time.
    
    float top = getPositionY()+getContentSize().height*getScale()*(1-getAnchorPoint().y);
    if (top < WIN_SIZE.height)
    {
        setPositionY(getPositionY() + (WIN_SIZE.height-top)/elasticity);
    }
    
    float bottom = getPositionY()-getContentSize().height*getScale()*getAnchorPoint().y;
    if (bottom > 0)
    {
        setPositionY(getPositionY() - bottom/elasticity);
    }
    
    float leftSide = getPositionX()-getContentSize().width*getScale()*getAnchorPoint().x;
    if (leftSide > 0)
    {
        setPositionX(getPositionX() - leftSide/elasticity);
    }
    
    float rightSide = getPositionX()+getContentSize().width*getScale()*(1-getAnchorPoint().x);
    if (rightSide < WIN_SIZE.width)
    {
        setPositionX(getPositionX() + (WIN_SIZE.width-rightSide)/elasticity);
    }
    
    // Keep the map's scale at a comfortable level.
    
    if (getScale() < MIN_SCALE)
    {
        setScale(getScale() + (MIN_SCALE-getScale())/2);
    }
    
    if (getScale() > MAX_SCALE)
    {
        setScale(MAX_SCALE + (getScale() - MAX_SCALE)/2);
    }
}

/**
 @brief     If the map is outside of its boundaries, snap it back smoothly.
 */
void Map::snapMapToTransformLimitations()
{
    // The length of time the snap should take.
    const float snapTime = 0.2f;
    
    // Figure out distance to move by.
    CCPoint distanceToMove;
    
    // Add the map's distance out-of-bounds on the top to the distanceToMove.
    distanceToMove.y += MAX(WIN_SIZE.height - (getPositionY()+getContentSize().height*getScale()*(1-getAnchorPoint().y)), 0);
    
    // Add the map's distance out-of-bounds on the bottom to the distanceToMove.
    distanceToMove.y -= MAX(getPositionY()-getContentSize().height*getScale()*getAnchorPoint().y, 0);
    
    // Add the map's distance out-of-bounds on the left side to the distanceToMove.
    distanceToMove.x -= MAX(getPositionX()-getContentSize().width*getScale()*getAnchorPoint().x, 0);
    
    // Add the map's distance out-of-bounds on the right side to the distanceToMove.
    distanceToMove.x += MAX(WIN_SIZE.width - (getPositionX()+getContentSize().width*getScale()*(1-getAnchorPoint().x)), 0);
    
    // Move the map by the distance we calculated.
    runAction(CCEaseOut::create(CCMoveBy::create(snapTime, distanceToMove), 3));
    
    
    // Scale the up or down to be within its scaling bounds.
    
    if (getScale() < MIN_SCALE)
    {
        runAction(CCEaseOut::create(CCScaleTo::create(snapTime, MIN_SCALE), 3));
    }
    
    if (getScale() > MAX_SCALE)
    {
        runAction(CCEaseOut::create(CCScaleTo::create(snapTime, MAX_SCALE), 3));
    }
}
