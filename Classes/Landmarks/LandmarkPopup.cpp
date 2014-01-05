//
//  LandmarkPopup.cpp
//  NewYorkGuide
//
//  Created by Clement Todd on 2013-12-19.
//
//

#include "LandmarkPopup.h"
#include "Defines.h"

using namespace cocos2d;

/**
 @brief     Create an popup that displays the information from a specified landmark and add it to the current scene.
 @param     landmark    The landmark whose info should be displayed.
 @return    A pointer to the popup that is created.
 */
LandmarkPopup* LandmarkPopup::showPopup(Landmark landmark)
{
    LandmarkPopup* popup = create(landmark);
    
    if (popup)
    {
        CCDirector::sharedDirector()->getRunningScene()->addChild(popup);
        return popup;
    }
    else
    {
        return NULL;
    }
}

/**
 @brief     Create a new Popup instance.
 @return    A pointer to the newly created Popup.
 */
LandmarkPopup* LandmarkPopup::create(Landmark landmark)
{
    LandmarkPopup *popup = new LandmarkPopup();
    if (popup && popup->init(landmark))
    {
        popup->autorelease();
        return popup;
    }
    CC_SAFE_DELETE(popup);
    return NULL;
}

/**
 @brief     Initialize this Popup instance.
 @return    Whether or not initialization was successful.
 */
bool LandmarkPopup::init(Landmark landmark)
{
    if (!Popup::init())
    {
        return false;
    }
    
    m_Landmark = landmark;
    
    addContent(CCLabelTTF::create(landmark.name, "Montserrat", 150 * SCREEN_SCALE));
    
    CCSprite* image = CCSprite::create(landmark.imageFileName);
    image->setScale(SCREEN_SCALE);
    addContent(image);
    
    addContent(CCLabelTTF::create(landmark.description, "Montserrat", 75 * SCREEN_SCALE));
    
    addButton("Close", CCCallFunc::create(this, callfunc_selector(LandmarkPopup::removeFromParent)), ccRED);
    
    return true;
}
