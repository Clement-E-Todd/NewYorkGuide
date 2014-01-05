//
//  LandmarkPopup.cpp
//  NewYorkGuide
//
//  Created by Clement Todd on 2013-12-19.
//
//

#include "LandmarkPopup.h"
#include "Defines.h"
#include "GoogleMapsLauncher.h"

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
    
    // Add title to top of page.
    addContent(CCLabelTTF::create(landmark.name, "Montserrat", 150 * SCREEN_SCALE));
    
    // Add the image illustrating the landmark.
    char fullFileName[64];
    sprintf(fullFileName, "%s.png", m_Landmark.imageFileName);
    m_Texture = CCTextureCache::sharedTextureCache()->addImage(fullFileName);
    CCSprite* image = CCSprite::createWithTexture(m_Texture);
    image->setScale(SCREEN_SCALE);
    addContent(image);
    
    // Add the description.
    addContent(CCLabelTTF::create(landmark.description, "Montserrat", 75 * SCREEN_SCALE));
    
    // If an address was provided, add a button to get directions to this landmark.
    if (landmark.address != NULL && landmark.address[0] != '\0')
    {
        addButton("Get Directions", CCCallFunc::create(this, callfunc_selector(LandmarkPopup::getDirections)), ccORANGE);
    }
    
    // Finally, add a button to close the popup.
    addButton("Close", CCCallFunc::create(this, callfunc_selector(LandmarkPopup::removeFromParent)), ccRED);
    
    return true;
}

/**
 @brief Called when the popup is removed from the node tree.
 */
void LandmarkPopup::onExit()
{
    // Remove the texture from the texture cache to free up memory.
    CCTextureCache::sharedTextureCache()->removeTexture(m_Texture);
    
    // Pass control along to the base class.
    Popup::onExit();
}

/**
 @brief     Display directions to this landmark with Google Maps.
 */
void LandmarkPopup::getDirections()
{
    GoogleMapsLauncher::showDirections(m_Landmark.address);
}
