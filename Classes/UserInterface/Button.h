//
//  Button.h
//  NewYorkGuide
//
//  Created by Clement Todd on 2013-12-19.
//
//

#ifndef BUTTON_H
#define BUTTON_H

#include "cocos2d.h"

/**
 @brief    A sprite node which will execute specified callbacks when touched and released.
 */
class Button : public cocos2d::CCSprite, public cocos2d::CCTouchDelegate
{
public:

    /**
     @brief     Create an instance of a Button with images and callbacks for both the "press" and "release" states.
     @param     imageFilename           The file name for the image to be used while the button is in its normal state.
     @param     pressedimageFilename    The file name for the image to be used while the button is in its pressed state.
     @param     callbackOnPress         The callback to execute when a touch on the button begins.
     @param     callbackOnRelease       The callback to execute when a touch on the button ends.
     @return    A pointer to the newly created Button.
     */
    static Button* create(const char* imageFilename, const char* pressedImageFilename,
                          cocos2d::CCCallFunc* callbackOnPress, cocos2d::CCCallFunc* callbackOnRelease);
    
    /**
     @brief     Create an instance of a Button with an image and callbacks for both the "press" and "release" states.
     @param     imageFilename           The file name for the image to be used while the button is in its normal state.
     @param     callbackOnPress         The callback to execute when a touch on the button begins.
     @param     callbackOnRelease       The callback to execute when a touch on the button ends.
     @return    A pointer to the newly created Button.
     */
    static Button* create(const char* imageFilename, cocos2d::CCCallFunc* callbackOnPress, cocos2d::CCCallFunc* callbackOnRelease);
    
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
    
    /**
     @brief     Checks whether or not the button is currently pressed.
     */
    bool isPressed();
    
protected:

    /**
     @brief     Initiaize an instance of a Button with images and callbacks for both the "press" and "release" states.
     @param     imageFilename           The file name for the image to be used while the button is in its normal state.
     @param     pressedimageFilename    The file name for the image to be used while the button is in its pressed state.
     @param     callbackOnPress         The callback to execute when a touch on the button begins.
     @param     callbackOnRelease       The callback to execute when a touch on the button ends.
     @return    Whether or not the Button was initialized successfully.
     */
    virtual bool init(const char* imageFilename, const char* pressedImageFilename,
              cocos2d::CCCallFunc* callbackOnPress, cocos2d::CCCallFunc* callbackOnRelease);
    
    /**
     @brief     Called when this is removed from the node tree.
     */
    virtual void onExit();
    
    /**
     @brief     An extendable method which is called when a new touch on the button begins.
     */
    virtual void onTouchBegan();
    
    /**
     @brief     An extendable method which is called when an existing touch moves off of the button.
     */
    virtual void onTouchMovedOff();
    
    /**
     @brief     An extendable method which is called when an existing touch moves back onto the button.
     */
    virtual void onTouchMovedOn();
    
    /**
     @brief     An extendable method which is called when a touch ends on the button.
     */
    virtual void onTouchEnded();
    
    /**
     @brief     Checks whether or not an indicated touch lies within the Button's bounds.
     @return    The result of the comparison.
     */
    bool touchIsInBounds(cocos2d::CCTouch* touch);
    
private:
    
    // The textures to display in the button's normal and pressed states, respectively.
    cocos2d::CCTexture2D* m_NormalTexture;
    cocos2d::CCTexture2D* m_PressedTexture;
    
    // The callbacks which should be executed when the button is pressed and released, respectively.
    cocos2d::CCCallFunc* m_CallbackOnPress;
    cocos2d::CCCallFunc* m_CallbackOnRelease;
    
};

#endif // BUTTON_H