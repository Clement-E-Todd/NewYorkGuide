//
//  LandmarkButton.h
//  NewYorkGuide
//
//  Created by Clement Todd on 2013-12-19.
//
//

#ifndef LANDMARK_BUTTON_H
#define LANDMARK_BUTTON_H

#include "cocos2d.h"
#include "Button.h"
#include "Landmark.h"

/**
 @brief     A button designed specifically for displaying information on a specified landmark.
 */
class LandmarkButton : public Button
{
public:
    
    /**
     @brief     Create a LandmarkButton instance.
     @param     landmark    The landmark data to display.
     @return    A pointer to the newly created button.
     */
    static LandmarkButton* create(Landmark landmark);
    
    /**
     @brief     Counteract the parent's scaling.
     @param     duration            How long it should take to go to the original scale.
     @param     futureParentScale   The scale that the parent is expected to be at at the end of the duration (use 0,0 for current).
     */
    void maintainOriginalScale(float duration = 0.0f, cocos2d::CCPoint futureParentScale = cocos2d::CCPointZero);
    
protected:
    
    /**
     @brief     Initialize a LandmarkButton instance.
     @param     landmark    The landmark data to display.
     @return    Whether or not the LandmarkButton was initialized successfully.
     */
    bool init(Landmark landmark);
    
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
     @brief     Called whenever any button in this popup is held down.
     */
    void onAnyButtonDown();
    
private:
    
    /** The landmark data to be displayed. */
    Landmark m_Landmark;
};

#endif // LANDMARK_BUTTON_H
