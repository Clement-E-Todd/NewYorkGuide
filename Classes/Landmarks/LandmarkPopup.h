//
//  LandmarkPopup.h
//  NewYorkGuide
//
//  Created by Clement Todd on 2013-12-19.
//
//

#ifndef LANDMARK_POPUP_H
#define LANDMARK_POPUP_H

#include "Popup.h"
#include "Landmark.h"

/**
 @brief     A popup designed to show the name, an image and a brief description of a landmark as well as providing options to get directions to the location or visit its website.
 */
class LandmarkPopup : public Popup
{
public:
    
    /**
     @brief     Create an popup that displays the information from a specified landmark and add it to the current scene.
     @param     landmark        The landmark whose info should be displayed.
     @param     buttonPosition  The position of the corresponding LandmarkButton (used for visual flare).
     @return    A pointer to the popup that is created.
     */
    static LandmarkPopup* showPopup(Landmark landmark, cocos2d::CCPoint buttonPosition);
    
protected:
    
    /**
     @brief     Create an popup that displays the information from a specified landmark.
     @param     landmark    The landmark whose info should be displayed.
     @param     buttonPosition  The position of the corresponding LandmarkButton (used for visual flare).
     @return    A pointer to the popup that is created.
     */
    static LandmarkPopup* create(Landmark landmark, cocos2d::CCPoint buttonPosition);
    
    /**
     @brief     Initialize this LandmarkPopup with its Landmark info.
     @param     landmark    The landmark whose info should be displayed.
     @param     buttonPosition  The position of the corresponding LandmarkButton (used for visual flare).
     @return    Whether or not the initialization was successful.
     */
    bool init(Landmark landmark, cocos2d::CCPoint buttonPosition);
    
    /**
     @brief Called when the popup is removed from the node tree.
     */
    void onExit();
    
    /**
     @brief     Display directions to this landmark with Google Maps.
     */
    void getDirections();
    
    /**
     @brief     Launch the landmark's official website.
     */
    void launchWebsite();
    
    /**
     @brief     Launch the website where tickets for the landmark can be purchased.
     */
    void launchTicketWebsite();
    
private:
    
    /** The Landmark data being presented by the popup. */
    Landmark m_Landmark;
    
    /** The texture used for the image. */
    cocos2d::CCTexture2D* m_Texture;
};

#endif // LANDMARK_POPUP_H
