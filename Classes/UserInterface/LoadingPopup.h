//
//  LoadingPopup.h
//  NewYorkGuide
//
//  Created by Clement Todd on 2014-01-05.
//
//

#ifndef LOADING_POPUP_H
#define LOADING_POPUP_H

#include "Popup.h"

/**
 @brief     An extension of CCSprite which is cropped to reflect a laoding value.
 */
class ProgressBar : public cocos2d::CCSprite
{
public:
    
    /**
     @brief     Create a progress bar using a specified image file.
     */
    static ProgressBar* create(const char *fileName);
    
    /**
     @brief     Visits this node's children and draw them recursively. Progress bar clips a chunk based on the progress value.
     */
    virtual void visit(void);
    
    /**
     @brief     Set the progress to be shown by this sprite.
     */
    void setProgress(float progress);
    
private:
    
    // The progress that this object is displaying (0 = none, 1 = complete)
    float m_Progress;
};

/**
 @brief     A popup especially for displaying a loading progress bar.
 */
class LoadingPopup : public Popup
{
public:
    
    /**
     @brief     Create and add a popup to the current scene.
     @return    A pointer to the popup.
     */
    static LoadingPopup* showPopup(cocos2d::CCSprite* borderSprite, ProgressBar* progressBar);
    
    /**
     @brief     Set the progress to be shown by the progress bar.
     */
    void setProgress(float progress);
    
protected:
    
    /**
     @brief     Create a new Popup instance.
     @return    A pointer to the newly created Popup.
     */
    static LoadingPopup* create(cocos2d::CCSprite* borderSprite, ProgressBar* progressBar);
    
    /**
     @brief     Initialize this instance.
     @return    Whether or not initialization was successful.
     */
    bool init(cocos2d::CCSprite* borderSprite, ProgressBar* progressBar);
    
private:
    
    // The sprite which surrounds the progress bar.
    cocos2d::CCSprite* m_Border;
    
    // The sprite which forms the progress bar.
    ProgressBar* m_ProgressBar;
    
};

#endif // LOADING_POPUP_H
