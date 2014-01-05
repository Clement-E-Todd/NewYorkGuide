//
//  CompositeSprite.h
//  NewYorkGuide
//
//  Created by Clement Todd on 2013-12-09.
//
//

#ifndef COMPOSITE_SPRITE_H
#define COMPOSITE_SPRITE_H

#include "cocos2d.h"
#include "Defines.h"
#include "LoadingPopup.h"
#include "HidingSprite.h"

class CompositeSprite;

/**
 @brief     An observer that gets notified with updates on the CompositeSprite's loading state.
 */
struct CompositeSpriteObserver
{
    /**
     @brief     Reaction to the end of a CompositeSprite's loading cycle.
     */
    virtual void compositeSpriteFinishedLoading(CompositeSprite* sprite) = 0;
};

/**
 @brief     A structure used by CompositeSprite to keep track of its loading progress.
 */
struct CompositeSpriteLoadData
{
    const char* fileName;
    const char* fileExtension;
    unsigned int gridWidth;
    unsigned int gridHeight;
    LoadingPopup* loadingPopup;
    
    std::vector<std::vector<HidingSprite*> > spriteGrid;
    unsigned int colomn;
    unsigned int row;
};

/**
 @brief    A node which loads in several other sprites and stitches them together to create sprites that can be larger than the device's maximum texture size.
 */
class CompositeSprite : public cocos2d::CCNode
{
public:
    
    /**
     @brief     Create an CompositeSprite instance with a grid of CCSprites.
     @param     fileName        The part of the file's name which comes before its alignment.
     @param     fileExtension   The file extension shared by all sprites in the grid.
     @param     gridWidth       The number of images to be found width-wise in the grid.
     @param     gridHeight      The number of images to be found height-wise in the grid.
     @param     loadingPopup    The popup which will visualize the process of initializing the composite sprite.
     @return    A pointer to the newly created CompositeSprite.
     */
    static CompositeSprite* create(const char *fileName, const char* fileExtension, unsigned int gridWidth, unsigned int gridHeight, LoadingPopup* loadingPopup);
    
    /**
     @brief     Subscribe an observer to loading notifications for this sprite.
     @param     observer    A pointer to the observer to be added.
     */
    void addObserver(CompositeSpriteObserver* observer);
    
    
protected:
    
    /**
     @brief     Initialize the CompositeSprite by populating it with its CCSprite children.
     @param     fileName        The part of the file's name which comes before its alignment.
     @param     fileExtension   The file extension shared by all sprites in the grid.
     @param     gridWidth       The number of images to be found width-wise in the grid.
     @param     gridHeight      The number of images to be found height-wise in the grid.
     @param     loadingPopup    The popup which will visualize the process of initializing the composite sprite.
     @return    true    The CompositeSprite was initialized successfully.
     @return    false   The CompositeSprite failed to initialize.
     */
    virtual bool init(const char* fileName, const char* fileExtension, unsigned int gridWidth, unsigned int gridHeight, LoadingPopup* loadingPopup);
    
    /**
     @brief     Load and add the next child sprite.
     */
    void loadNextPiece();
    
private:
    
    // Information regarding the sprite's loading progress.
    CompositeSpriteLoadData m_LoadingData;
    
    // A collection of the observers that are subscribed to notifications from this sprite.
    std::vector<CompositeSpriteObserver*> m_Observers;
};

#endif // COMPOSITE_SPRITE_H
