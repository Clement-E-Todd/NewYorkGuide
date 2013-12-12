//
//  MapNavigator.h
//  NewYorkGuide
//
//  Created by Clement Todd on 2013-12-11.
//
//

#ifndef MAP_NAVIGATOR_H
#define MAP_NAVIGATOR_H

#include "cocos2d.h"

/**
 @brief    A node which takes user input to navigate around a map node.
 */
class MapNavigator : public cocos2d::CCNode, public cocos2d::CCTouchDelegate
{
public:
    
    /**
     @brief     Create an MapNavigator instance with a target map node.
     @param     mapNode     The map which should be manipulated by the navigator.
     @return    A pointer to the newly created MapNavigator.
     */
    static MapNavigator* create(cocos2d::CCNode* mapNode);
    
    /**
     @brief     Respond to the beginning of a user's touch.
     @param     pTouch      A pointer to the touch information.
     @param     pEvent      The event data.
     @return    Whether or not the map navigator accepted the touch input.
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
     @brief     Initialize the map navigator with its target map node.
     @param     mapNode     The map which should be manipulated by the navigator.
     @return    Whether or not the initialization was successful.
     */
    bool init(cocos2d::CCNode* mapNode);
    
    /**
     @brief     Called when the map navigator is removed from the node tree.
     */
    void onExit();
    
private:
    
    // The node which is manipulated by the MapNavigator.
    cocos2d::CCNode* m_MapNode;
    
    // Pointers to the touch input data (we only care about 2 touches at once, so that's all we store).
    cocos2d::CCTouch* m_Touches[2];
    
    // Positional data used to calculate panning and zooming.
    cocos2d::CCPoint m_MapNodeStartPosition;
    float m_MapNodeStartScale;
    cocos2d::CCPoint m_TouchStartPositions[2];
};

#endif // MAP_NAVIGATOR_H
