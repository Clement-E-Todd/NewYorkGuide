//
//  Button.cpp
//  NewYorkGuide
//
//  Created by Clement Todd on 2013-12-19.
//
//

#include "Button.h"

using namespace cocos2d;

// Create an instance of a Button with images and callbacks for both the "press" and "release" states.

Button* Button::create(const char* imageFilename, const char* pressedImageFilename,
                      cocos2d::CCCallFunc* callbackOnPress, cocos2d::CCCallFunc* callbackOnRelease)
{
    Button *button = new Button();
    if (button && button->init(imageFilename, pressedImageFilename, callbackOnPress, callbackOnRelease))
    {
        button->autorelease();
        return button;
    }
    CC_SAFE_DELETE(button);
    return NULL;
}

// Create an instance of a Button with an image and callbacks for both the "press" and "release" states.

Button* Button::create(const char* imageFilename, cocos2d::CCCallFunc* callbackOnPress, cocos2d::CCCallFunc* callbackOnRelease)
{
    return create(imageFilename, imageFilename, callbackOnPress, callbackOnRelease);
}

// Initiaize an instance of a Button with images and callbacks for both the "press" and "release" states.

bool Button::init(const char* imageFilename, const char* pressedImageFilename,
          cocos2d::CCCallFunc* callbackOnPress, cocos2d::CCCallFunc* callbackOnRelease)
{
    // Attempt to load the indicated textures.
    CCTextureCache* cache = CCTextureCache::sharedTextureCache();
    m_NormalTexture = cache->addImage(imageFilename);
    m_PressedTexture = cache->addImage(pressedImageFilename);
    
    // If either of the texture failed to load, or if the normal texture can't be used, initialization has failed.
    if (!m_NormalTexture ||
        !m_PressedTexture ||
        !initWithTexture(m_NormalTexture))
    {
        return false;
    }
    
    // As initialization has now succeeded, register this Button with the touch dispatcher.
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, false);
    
    // And finally, register the indicated callbacks.
    m_CallbackOnPress = callbackOnPress;
    m_CallbackOnRelease = callbackOnRelease;
    
    // Retain the callbacks so that cocos2d's garbage collector doesn't take them.
    if (m_CallbackOnPress)   m_CallbackOnPress->retain();
    if (m_CallbackOnRelease) m_CallbackOnRelease->retain();
    
    // By default, sliding your finger after touching the Button will not cncel the touch.
    m_TouchMoveAllowed = true;
    
    return true;
}

// Called when this is removed from the node tree.

void Button::onExit()
{
    // Unregister this Button from the touch dispatcher.
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
    // Allow the callbacks to be taken by cocos2d's garbage collector.
    if (m_CallbackOnPress)   m_CallbackOnPress->autorelease();
    if (m_CallbackOnRelease) m_CallbackOnRelease->autorelease();
    
    // Pass the onExit() call along to the base class.
    CCSprite::onExit();
}

// Respond to the beginning of a user's touch.

bool Button::ccTouchBegan(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    // Perform the extendable "touch began" behaviour and note that this touch hasn't moved yet.
    if (touchIsInBounds(pTouch))
    {
        onTouchBegan();
        m_TouchMoved = false;
        return true;
    }
    
    // Or ignore the touch if it didn't intersect with the Button.
    else
    {
        return false;
    }
}

// Respond to the user's continued touch input.

void Button::ccTouchMoved(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    // Make sure that Touch Move is allowed by this button before continuing.
    if (!m_TouchMoveAllowed)
    {
        if (!m_TouchMoved)
        {
            m_TouchMoved = true;
            onTouchMovedOff();
        }
        
        return;
    }
    
    // Perform the extendable "touch moved off of button" behaviour if applicable...
    if (isPressed() && !touchIsInBounds(pTouch))
    {
        onTouchMovedOff();
    }
    
    // ...Or perform the extendable "touch moved back onto button" behaviour if applicable.
    else if (!isPressed() && touchIsInBounds(pTouch))
    {
        onTouchMovedOn();
    }
}

// Respond to the end of a user's touch.

void Button::ccTouchEnded(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    // In the event that this Button disallows Touch Moves and a Touch Move was detected, ignore the Touch End logic.
    if (!m_TouchMoveAllowed && m_TouchMoved)
    {
        return;
    }
    
    // Perform the extendable "touch ended" behaviour.
    if (touchIsInBounds(pTouch))
    {
        onTouchEnded();
    }
}

// Respond to a user's touch input being lost.

void Button::ccTouchCancelled(cocos2d::CCTouch *pTouch, cocos2d::CCEvent *pEvent)
{
    // Lost touches should be handled the same as other ended touches.
    ccTouchEnded(pTouch, pEvent);
}

// An extendable method which is called when a new touch on the button begins.

void Button::onTouchBegan()
{
    // Execute the assigned callback for this event.
    if (m_CallbackOnPress) m_CallbackOnPress->execute();
    
    // Display the "pressed" texture since the button is being touched.
    setTexture(m_PressedTexture);
}

// An extendable method which is called when an existing touch moves off of the button.
 
void Button::onTouchMovedOff()
{
    // Display the "normal" texture since the button is not being touched.
    setTexture(m_NormalTexture);
}

// An extendable method which is called when an existing touch moves back onto the button.

void Button::onTouchMovedOn()
{
    // Display the "pressed" texture since the button is being touched.
    setTexture(m_PressedTexture);
}

// An extendable method which is called when a touch ends on the button.

void Button::onTouchEnded()
{
    // Execute the assigned callback for this event.
    if (m_CallbackOnRelease) m_CallbackOnRelease->execute();
    
    // Display the "normal" texture since the button is not being touched.
    setTexture(m_NormalTexture);
}

// Checks whether or not the button is currently pressed.
 
bool Button::isPressed()
{
    return (getTexture() == m_PressedTexture);
}

// Checks whether or not an indicated touch lies within the Button's bounds.
 
bool Button::touchIsInBounds(cocos2d::CCTouch* touch)
{
    CCPoint touchPositionLocal = convertToNodeSpace(touch->getLocation());
    
    return (touchPositionLocal.x > 0 && touchPositionLocal.x <= getContentSize().width &&
            touchPositionLocal.y > 0 && touchPositionLocal.y <= getContentSize().height);
}

// Set whether or not the Button will stay selected if the user's touch moves.

void Button::allowTouchMovement(bool allow)
{
    m_TouchMoveAllowed = allow;
}
