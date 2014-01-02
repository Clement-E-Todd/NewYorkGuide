//
//  Popup.h
//  NewYorkGuide
//
//  Created by Clement Todd on 2013-12-28.
//
//

#ifndef POPUP_H
#define POPUP_H

#include "cocos2d.h"
#include "Button.h"

/**
 @brief     A node which displays a specified set of content with maximum draw priority to the user while blocking input to other elements behind it.
 */
class Popup : public cocos2d::CCNode, public cocos2d::CCTouchDelegate
{
public:
    
    /**
     @brief     Create and add a popup to the current scene.
     @return    A pointer to the popup.
     */
    static Popup* showPopup();
    
    /**
     @brief     Add a node to the popup. The node will be positioned automatically.
     */
    void addContent(cocos2d::CCNode* content);
    
    /**
     @brief     Add a button to the popup with specified text, callback and colour. The button will be positioned automatically.
     */
    void addButton(const char* text, cocos2d::CCCallFunc* callback, cocos2d::ccColor3B colour);
    
    /**
     @brief     Respond to the beginning of a user's touch. Will always return true in order to claim the touch and block input to other elements behind it.
     @param     pTouch      A pointer to the touch information.
     @param     pEvent      The event data.
     @return    Whether or not the map  accepted the touch input.
     */
    bool ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent) { return true; }
    
protected:
    
    /**
     @brief     Create a new Popup instance.
     @return    A pointer to the newly created Popup.
     */
    static Popup* create();
    
    /**
     @brief     Initialize this Popup instance.
     @return    Whether or not initialization was successful.
     */
    bool init();
    
    /**
     @brief     Called when this is removed from the node tree.
     */
    virtual void onExit();
    
    /**
     @brief     Position all elements added to the popup in an evenly-spaced manner.
     */
    void organizeContent();
    
private:
    
    // A list of all of the popup's normal contents (titles, text, images etc).
    std::vector<cocos2d::CCNode*> m_Contents;
    
    // A list of all of the popup's butons.
    std::vector<Button*> m_Buttons;
    
};

#endif // POPUP_H
