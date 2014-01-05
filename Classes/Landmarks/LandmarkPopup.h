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
     @param     landmark    The landmark whose info should be displayed.
     @return    A pointer to the popup that is created.
     */
    static LandmarkPopup* showPopup(Landmark landmark);
    
protected:
    
    /**
     @brief     Create an popup that displays the information from a specified landmark.
     @param     landmark    The landmark whose info should be displayed.
     @return    A pointer to the popup that is created.
     */
    static LandmarkPopup* create(Landmark landmark);
    
    /**
     @brief     Initialize this LandmarkPopup with its Landmark info.
     @param     landmark    The landmark whose info should be displayed.
     @return    Whether or not the initialization was successful.
     */
    bool init(Landmark landmark);
    
private:
    
    // The Landmark data being presented by the popup
    Landmark m_Landmark;
};

#endif // LANDMARK_POPUP_H
