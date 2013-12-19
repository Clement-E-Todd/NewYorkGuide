//
//  Map.h
//  NewYorkGuide
//
//  Created by Clement Todd on 2013-12-11.
//
//

#ifndef MAP_H
#define MAP_H

#include "cocos2d.h"

/**
 @brief    A controller which manages the behaviour of and interaction with nodes that represent a map.
 */
class Map : public cocos2d::CCNode, public cocos2d::CCTouchDelegate
{
public:
    
    /**
     @brief     Create a Map instance with a target map node.
     @param     mapNode     The node which visually represents the map.
     @return    A pointer to the newly created Map.
     */
    static Map* create(cocos2d::CCNode* mapNode);
    
    /**
     @brief     Respond to the beginning of a user's touch.
     @param     pTouch      A pointer to the touch information.
     @param     pEvent      The event data.
     @return    Whether or not the map  accepted the touch input.
     */
    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    /**
     @brief     Respond to the user's continued touch input.
     @param     pTouch      A pointer to the touch information.
     @param     pEvent      The event data.
     */
    void ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    /**
     @brief     Respond to the end of a user's touch.
     @param     pTouch      A pointer to the touch information.
     @param     pEvent      The event data.
     */
    void ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
    /**
     @brief     Respond to a user's touch input being lost.
     @param     pTouch      A pointer to the touch information.
     @param     pEvent      The event data.
     */
    void ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent);
    
protected:
    
    /**
     @brief     Initialize the map with its target map node.
     @param     mapNode     The node which visually represents the map.
     @return    Whether or not the initialization was successful.
     */
    bool init(cocos2d::CCNode* mapNode);
    
    /**
     @brief     Called when this is removed from the node tree.
     */
    void onExit();
    
    /**
     @brief     Record any necessary information in anticipation of panning.
     @return    Whether or not the conditions for panning were met; this method will only succeed if we are tracking exactly one touch.
     */
    bool setUpForPanning();
    
    /**
     @brief     Record any necessary information in anticipation of zooming.
     @return    Whether or not the conditions for zooming were met; this method will only succeed if we are tracking two touches.
     */
    bool setUpForZooming();
    
    /**
     @brief     Translate a point on-screen (for example, a touch location) into an anchor point for the map node.
     @param     location    The on-screen position to be translated.
     @return    The resulting anchor point.
     */
    cocos2d::CCPoint getAnchorPointFromLocation(cocos2d::CCPoint location);
    
    /**
     @brief     If the map is outside of its boundaries, snap it back smoothly.
     */
    void snapMapToTransformLimitations();
    
private:
    
    // The node which visually represents the map.
    cocos2d::CCNode* m_MapNode;
    
    // Pointers to the touch input data (we only care about 2 touches at once, so that's all we store).
    cocos2d::CCTouch* m_Touches[2];
    
    // Positional data used to calculate panning and zooming.
    cocos2d::CCPoint m_MapNodeStartPosition;
    float m_MapNodeStartScale;
    cocos2d::CCPoint m_TouchStartPositions[2];
};

#endif // MAP_H
