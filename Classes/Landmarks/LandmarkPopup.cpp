//
//  LandmarkPopup.cpp
//  NewYorkGuide
//
//  Created by Clement Todd on 2013-12-19.
//
//

#include "LandmarkPopup.h"
#include "Defines.h"
#include "WebLauncher.h"

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

    if (landmark.websiteURL != NULL && landmark.websiteURL[0] != '\0')
    {
        addButton("Visit Website", CCCallFunc::create(this, callfunc_selector(LandmarkPopup::launchWebsite)), ccBLUE);
    }
    
    if (landmark.ticketsURL != NULL && landmark.ticketsURL[0] != '\0')
    {
        addButton("Get Tickets", CCCallFunc::create(this, callfunc_selector(LandmarkPopup::launchTicketWebsite)), ccYELLOW);
    }
    
    addButton("Close", CCCallFunc::create(this, callfunc_selector(LandmarkPopup::removeFromParent)), ccRED);
    
    return true;
}

/**
 @brief     Launch the landmark's official website.
 */
void LandmarkPopup::launchWebsite()
{
    if (m_Landmark.websiteURL != NULL && m_Landmark.websiteURL[0] != '\0')
    {
        WebLauncher::launchBrowserWithURL(m_Landmark.websiteURL);
    }
}

/**
 @brief     Launch the website where tickets for the landmark can be purchased.
 */
void LandmarkPopup::launchTicketWebsite()
{
    if (m_Landmark.ticketsURL != NULL && m_Landmark.ticketsURL[0] != '\0')
    {
        WebLauncher::launchBrowserWithURL(m_Landmark.ticketsURL);
    }
}
