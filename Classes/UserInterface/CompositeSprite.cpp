//
//  CompositeSprite.cpp
//  NewYorkGuide
//
//  Created by Clement Todd on 2013-12-09.
//
//

#include "CompositeSprite.h"
#include "HidingSprite.h"

using namespace std;
using namespace cocos2d;

/**
 @brief     Create an CompositeSprite instance with a grid of sprites.
 @param     fileName        The part of the file's name which comes before its alignment.
 @param     fileExtension   The file extension shared by all sprites in the grid.
 @param     gridWidth       The number of images to be found width-wise in the grid.
 @param     gridHeight      The number of images to be found height-wise in the grid.
 @return    A pointer to the newly created CompositeSprite.
 */
CompositeSprite* CompositeSprite::create(const char *fileName, const char* fileExtension, unsigned int gridWidth, unsigned int gridHeight)
{
    CompositeSprite *compositeSprite = new CompositeSprite();
    if (compositeSprite && compositeSprite->init(fileName, fileExtension, gridWidth, gridHeight))
    {
        compositeSprite->autorelease();
        return compositeSprite;
    }
    CC_SAFE_DELETE(compositeSprite);
    return NULL;
}

/**
 @brief     Initialize the CompositeSprite by populating it with its sprite children.
 @param     fileName        The part of the file's name which comes before its alignment.
 @param     fileExtension   The file extension shared by all sprites in the grid.
 @param     gridWidth       The number of images to be found width-wise in the grid.
 @param     gridHeight      The number of images to be found height-wise in the grid.
 @return    true    The CompositeSprite was initialized successfully.
 @return    false   The CompositeSprite failed to initialize.
 */
bool CompositeSprite::init(const char *fileName, const char* fileExtension, unsigned int gridWidth, unsigned int gridHeight)
{
    // Find a group of image files beginning in [fileName] and ending in [fileExtension] with grid position indicated between (ie. "imageName3x2.png") and load each of them in as HidingSprites, adding them as children in a grid.
    CCLOG("*** Creating a CompositeSprite using files beginning with \"%s\" and ending with \"%s\".", fileName, fileExtension);
    
    vector<vector<HidingSprite*> > spriteGrid;
    
    // Populate the sprite grid with HidingSprites, positioning each one correctly and updating the CompositeSprite's content size.
    for (unsigned int colomn = 0; colomn < gridWidth; colomn++)
    {
        spriteGrid.push_back(vector<HidingSprite*>());
        
        for (unsigned int row = 0; row < gridHeight; row++)
        {
            // Get the full file name for the next image to be used.
            string fullFileName = fileName;
            
            char colomnString[8];
            sprintf(colomnString, "%u", colomn);
            fullFileName += colomnString;
            
            fullFileName += "x";
            
            char rowString[8];
            sprintf(rowString, "%u", row);
            fullFileName += rowString;
            
            fullFileName += string(fileExtension);
            
            // Attempt to load a file with the specified name.
            HidingSprite* sprite = HidingSprite::create(fullFileName.c_str());
            
            if (sprite)
            {
                // If the indicated image is succesfully loaded, add it and continue.
                CCLOG("Adding image \"%s\" to CompositeSprite.", fullFileName.c_str());
                addChild(sprite);
                spriteGrid[colomn].push_back(sprite);
                
                // Place the newly added sprite in its correct position.
                sprite->setPosition(ccp(sprite->getContentSize().width/2, sprite->getContentSize().height/2));
                for (int i = 0; i < colomn; i++)
                {
                    // Add to the image's X position
                    sprite->setPositionX(sprite->getPositionX() + spriteGrid[i][row]->getContentSize().width);
                }
                for (int i = 0; i < row; i++)
                {
                    // Add to the image's Y position
                    sprite->setPositionY(sprite->getPositionY() + spriteGrid[colomn][i]->getContentSize().height);
                }
                
                // Update the CompositeSprite's content size.
                setContentSize(CCSizeMake(MAX(getContentSize().width, sprite->getPositionX() + sprite->getContentSize().width/2),
                                          MAX(getContentSize().height, sprite->getPositionY() + sprite->getContentSize().height/2)));
            }
            else
            {
                // If the image did not load it means that the grid is incomplete and initialization has failed.
                removeAllChildrenWithCleanup(true);
                CCLOG("Failed to load \"%s\". Aborting.", fullFileName.c_str());
                return false;
            }
        }
    }
    
    // The CompositeSprite's anchor point will be in the middle by default.
    setAnchorPoint(ccp(0.5f, 0.5f));
    
    return getChildrenCount() > 0;
}
