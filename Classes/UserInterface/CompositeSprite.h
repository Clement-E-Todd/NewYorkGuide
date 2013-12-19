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
     @return    A pointer to the newly created CompositeSprite.
     */
    static CompositeSprite* create(const char *fileName, const char* fileExtension, unsigned int gridWidth, unsigned int gridHeight);
    
protected:
    
    /**
     @brief     Initialize the CompositeSprite by populating it with its CCSprite children.
     @param     fileName        The part of the file's name which comes before its alignment.
     @param     fileExtension   The file extension shared by all sprites in the grid.
     @param     gridWidth       The number of images to be found width-wise in the grid.
     @param     gridHeight      The number of images to be found height-wise in the grid.
     @return    true    The CompositeSprite was initialized successfully.
     @return    false   The CompositeSprite failed to initialize.
     */
    virtual bool init(const char *fileName, const char* fileExtension, unsigned int gridWidth, unsigned int gridHeight);
};

#endif // COMPOSITE_SPRITE_H
