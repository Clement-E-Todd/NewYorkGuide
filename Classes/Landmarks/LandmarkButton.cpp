//
//  LandmarkButton.cpp
//  NewYorkGuide
//
//  Created by Clement Todd on 2013-12-19.
//
//

#include "LandmarkButton.h"
#include "Defines.h"
#include "LandmarkPopup.h"

using namespace cocos2d;

// A tag used to identify the CCAction that LandmarkButton::maintainOriginalScale(...) uses.
#define TAG_SCALE_ACTION    12345

// Create a LandmarkButton instance.

LandmarkButton* LandmarkButton::create(Landmark landmark)
{
    LandmarkButton *button = new LandmarkButton();
    if (button && button->init(landmark))
    {
        button->autorelease();
        return button;
    }
    CC_SAFE_DELETE(button);
    return NULL;
}

// Initialize a LandmarkButton instance.

bool LandmarkButton::init(Landmark landmark)
{
    // Perform the base class initialization, or quit now if it fails.
    if (!Button::init("landmarkButtonNormal.png", "landmarkButtonPressed.png", NULL, NULL))
    {
        return false;
    }
    
    // Record the landmark data so that the Button can use it to create a LandmarkPopup when it is touched.
    m_Landmark = landmark;
    
    // If the user's finger moves between touching and releasing the LandmarkButton, the touch should be rejected.
    allowTouchMovement(false);
    
    // Create a thumbnail sprite using the image file indicated by the landmark data.
    char fullFileName[64];
    sprintf(fullFileName, "%s_mini.png", m_Landmark.imageFileName);
    CCSprite* thumbnail = CCSprite::create(fullFileName);
    
    // If the thumbnail was created successfully, add it as a child and end initialization.
    if (thumbnail)
    {
        addChild(thumbnail);
        thumbnail->setPosition(ccp(getContentSize().width/2, getContentSize().height/2));
        
        return true;
    }
    
    // Otherwise, initialization has failed and we will abort.
    else
    {
        return false;
    }
}

// Counteract the parent's scaling.

void LandmarkButton::maintainOriginalScale(float duration, cocos2d::CCPoint futureParentScale)
{
    // Figure out whether to use the parent's current scale or a predicted future scale.
    CCPoint parentScale;
    if (futureParentScale.x == 0 && futureParentScale.y == 0)
    {
        parentScale = ccp(getParent()->getScaleX(), getParent()->getScaleY());
    }
    else
    {
        parentScale = futureParentScale;
    }
    
    // Using that information, figure out what scale to scale this Button to.
    CCPoint newButtonScale = ccpMult(ccp((parentScale.x != 0) ? SCREEN_SCALE / parentScale.x : 0,
                                         (parentScale.y != 0) ? SCREEN_SCALE / parentScale.y : 0),
                                     isPressed() ? 1 : 0.75f);
    
    // Since we now have a new scaling goal, stop any existing scaling action.
    CCAction* scalingAction = getActionByTag(TAG_SCALE_ACTION);
    if (scalingAction)
    {
        stopActionByTag(TAG_SCALE_ACTION);
    }
    
    // If the new scaling action is instant, just set the scale directly.
    if (duration == 0.0f)
    {
        setScaleX(newButtonScale.x);
        setScaleY(newButtonScale.y);
    }
    
    // If the new scaling action is meant to be gradual, use a CCAction.
    else
    {
        CCAction* scalingAction = CCEaseOut::create(CCScaleTo::create(duration, newButtonScale.x, newButtonScale.y), 3);
        scalingAction->setTag(TAG_SCALE_ACTION);
        runAction(scalingAction);
    }
}

// An extendable method which is called when a new touch on the button begins.

void LandmarkButton::onTouchBegan()
{
    // Pass control on to the base class.
    Button::onTouchBegan();
    
    // Update the Button's scale.
    maintainOriginalScale();
    
    // Set the z order to be in front of other buttons.
    setZOrder(1);
}

// An extendable method which is called when an existing touch moves off of the button.
 
void LandmarkButton::onTouchMovedOff()
{
    // Pass control on to the base class.
    Button::onTouchMovedOff();
    
    // Update the Button's scale.
    maintainOriginalScale();
    
    // Set the z order to be on same level as other buttons.
    setZOrder(0);
}

// An extendable method which is called when an existing touch moves back onto the button.

void LandmarkButton::onTouchMovedOn()
{
    // Pass control on to the base class.
    Button::onTouchMovedOn();
    
    // Update the Button's scale.
    maintainOriginalScale();
    
    // Set the z order to be in front of other buttons.
    setZOrder(1);
}

// An extendable method which is called when a touch ends on the button.

void LandmarkButton::onTouchEnded()
{
    // Pass control on to the base class.
    Button::onTouchEnded();
    
    // Update the Button's scale.
    maintainOriginalScale();
    
    // Set the z order to be on same level as other buttons.
    setZOrder(0);
    
    // Display the popup.
    LandmarkPopup::showPopup(m_Landmark, convertToWorldSpaceAR(CCPointZero));
}
