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
#include "WebLauncher.h"

#define COLOUR_BUTTON_NORMAL    ccc3(0, 150, 141)
#define COLOUR_BUTTON_CLOSE     ccc3(0, 92, 115)

using namespace cocos2d;

// Create an popup that displays the information from a specified landmark and add it to the current scene.

LandmarkPopup* LandmarkPopup::showPopup(Landmark landmark, cocos2d::CCPoint buttonPosition)
{
    LandmarkPopup* popup = create(landmark, buttonPosition);
    
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

// Create a new Popup instance.
 
LandmarkPopup* LandmarkPopup::create(Landmark landmark, cocos2d::CCPoint buttonPosition)
{
    LandmarkPopup *popup = new LandmarkPopup();
    if (popup && popup->init(landmark, buttonPosition))
    {
        popup->autorelease();
        return popup;
    }
    CC_SAFE_DELETE(popup);
    return NULL;
}

// Initialize this Popup instance.

bool LandmarkPopup::init(Landmark landmark, cocos2d::CCPoint buttonPosition)
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
        addButton("Get Directions", CCCallFunc::create(this, callfunc_selector(LandmarkPopup::getDirections)), COLOUR_BUTTON_NORMAL);
    }
    
    // If a website URL was provided, add a linking button.
    if (landmark.websiteURL != NULL && landmark.websiteURL[0] != '\0')
    {
        addButton("Visit Website", CCCallFunc::create(this, callfunc_selector(LandmarkPopup::launchWebsite)), COLOUR_BUTTON_NORMAL);
    }
    
    // If a ticketing URL was provided, add a linking button
    if (landmark.ticketsURL != NULL && landmark.ticketsURL[0] != '\0')
    {
        addButton("Get Tickets", CCCallFunc::create(this, callfunc_selector(LandmarkPopup::launchTicketWebsite)), COLOUR_BUTTON_NORMAL);
    }
    
    // Finally, add a button to close the popup.
    addButton("Close", CCCallFunc::create(this, callfunc_selector(LandmarkPopup::closePopup)), COLOUR_BUTTON_CLOSE);
    
    
    // For visual flare, do a nice fade-in and make the illusion of the image moving from the button to the popup.
    const float duration = 0.35f;
    const float rate = 2.75f;
    
    GLubyte backdropOpacity = m_Backdrop->getOpacity();
    fadeInAllDecendants(duration, rate, this);
    m_Backdrop->stopAllActions();
    m_Backdrop->setOpacity(0);
    m_Backdrop->runAction(CCEaseOut::create(CCFadeTo::create(duration, backdropOpacity), rate));
    
    image->stopAllActions();
    CCPoint imagePosition = image->getPosition();
    float imageScale = image->getScale();
    image->setPosition(buttonPosition);
    image->setOpacity(255);
    image->setScale(imageScale*0.375f);
    image->runAction(CCMoveTo::create(duration, imagePosition));
    image->runAction(CCScaleTo::create(duration, imageScale));
    
    return true;
}

// Called when the popup is removed from the node tree.

void LandmarkPopup::onExit()
{
    // Remove the texture from the texture cache to free up memory.
    CCTextureCache::sharedTextureCache()->removeTexture(m_Texture);
    
    // Pass control along to the base class.
    Popup::onExit();
}

// Display directions to this landmark with Google Maps.
 
void LandmarkPopup::getDirections()
{
    GoogleMapsLauncher::showDirections(m_Landmark.address);
}

// Launch the landmark's official website.

void LandmarkPopup::launchWebsite()
{
    if (m_Landmark.websiteURL != NULL && m_Landmark.websiteURL[0] != '\0')
    {
        WebLauncher::launchBrowserWithURL(m_Landmark.websiteURL);
    }
}

// Launch the website where tickets for the landmark can be purchased.
 
void LandmarkPopup::launchTicketWebsite()
{
    if (m_Landmark.ticketsURL != NULL && m_Landmark.ticketsURL[0] != '\0')
    {
        WebLauncher::launchBrowserWithURL(m_Landmark.ticketsURL);
    }
}
