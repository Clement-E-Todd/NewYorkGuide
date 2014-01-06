//
//  CompositeSprite.cpp
//  NewYorkGuide
//
//  Created by Clement Todd on 2013-12-09.
//
//

#include "CompositeSprite.h"

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
CompositeSprite* CompositeSprite::create(const char *fileName, const char* fileExtension, unsigned int gridWidth, unsigned int gridHeight, LoadingPopup* loadingPopup)
{
    CompositeSprite *compositeSprite = new CompositeSprite();
    if (compositeSprite && compositeSprite->init(fileName, fileExtension, gridWidth, gridHeight, loadingPopup))
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
bool CompositeSprite::init(const char *fileName, const char* fileExtension, unsigned int gridWidth, unsigned int gridHeight, LoadingPopup* loadingPopup)
{
    // Find a group of image files beginning in [fileName] and ending in [fileExtension] with grid position indicated between (ie. "imageName3x2.png") and load each of them in as HidingSprites, adding them as children in a grid.
    CCLOG("*** Creating a CompositeSprite using files beginning with \"%s\" and ending with \"%s\".", fileName, fileExtension);
    
    // Set all of the data that will be needed to load.
    m_LoadingData.fileName = fileName;
    m_LoadingData.fileExtension = fileExtension;
    m_LoadingData.gridWidth = gridWidth;
    m_LoadingData.gridHeight = gridHeight;
    m_LoadingData.loadingPopup = loadingPopup;
    
    m_LoadingData.colomn = 0;
    m_LoadingData.row = 0;
    
    // The CompositeSprite's anchor point will be in the middle by default.
    setAnchorPoint(ccp(0.5f, 0.5f));
    
    // Load the first piece after a brief pause to allow for the UI to update.
    runAction(CCSequence::create(CCDelayTime::create(1.0f / 60),
                                 CCCallFunc::create(this, callfunc_selector(CompositeSprite::loadNextPiece)),
                                 NULL));
    
    return true;
}

/**
 @brief     Subscribe an observer to loading notifications for this sprite.
 @param     observer    A pointer to the observer to be added.
 */
void CompositeSprite::addObserver(CompositeSpriteObserver* observer)
{
    if (observer)
    {
        m_Observers.push_back(observer);
    }
}

/**
 @brief     Load and add the next child sprite.
 */
void CompositeSprite::loadNextPiece()
{
    // Add a new colomn if needed
    if (m_LoadingData.row == 0)
    {
        m_LoadingData.spriteGrid.push_back(vector<HidingSprite*>());
    }
    
    // Get the full file name for the next image to be used.
    string fullFileName = m_LoadingData.fileName;
    
    char colomnString[8];
    sprintf(colomnString, "%u", m_LoadingData.colomn);
    fullFileName += colomnString;
    
    fullFileName += "x";
    
    char rowString[8];
    sprintf(rowString, "%u", m_LoadingData.row);
    fullFileName += rowString;
    
    fullFileName += string(m_LoadingData.fileExtension);
    
    // Attempt to load a file with the specified name.
    HidingSprite* sprite = HidingSprite::create(fullFileName.c_str());
    
    if (sprite)
    {
        // If the indicated image is succesfully loaded, add it and continue.
        CCLOG("Adding image \"%s\" to CompositeSprite.", fullFileName.c_str());
        addChild(sprite);
        m_LoadingData.spriteGrid[m_LoadingData.colomn].push_back(sprite);
        
        // Place the newly added sprite in its correct position.
        sprite->setPosition(ccp(sprite->getContentSize().width/2, sprite->getContentSize().height/2));
        for (int i = 0; i < m_LoadingData.colomn; i++)
        {
            // Add to the image's X position
            sprite->setPositionX(sprite->getPositionX() + m_LoadingData.spriteGrid[i][m_LoadingData.row]->getContentSize().width);
        }
        for (int i = 0; i < m_LoadingData.row; i++)
        {
            // Add to the image's Y position
            sprite->setPositionY(sprite->getPositionY() + m_LoadingData.spriteGrid[m_LoadingData.colomn][i]->getContentSize().height);
        }
        
        // Update the CompositeSprite's content size.
        setContentSize(CCSizeMake(MAX(getContentSize().width, sprite->getPositionX() + sprite->getContentSize().width/2),
                                  MAX(getContentSize().height, sprite->getPositionY() + sprite->getContentSize().height/2)));
    }
    else
    {
        // If the image did not load it means that the grid is incomplete and initialization has failed.
        CCLOG("Failed to load \"%s\". Aborting.", fullFileName.c_str());
        m_LoadingData.loadingPopup->removeFromParentAndCleanup(true);
        removeFromParentAndCleanup(true);
    }
    
    // Find out which row and colomn the next piece should be loaded for.
    m_LoadingData.row++;
    if (m_LoadingData.row >= m_LoadingData.gridHeight)
    {
        m_LoadingData.row = 0;
        m_LoadingData.colomn++;
    }
    
    // Update the loading popup
    float totalSprites = m_LoadingData.gridWidth * m_LoadingData.gridHeight;
    float loadedSprites = m_LoadingData.colomn*m_LoadingData.gridHeight + m_LoadingData.row;
    m_LoadingData.loadingPopup->setProgress(loadedSprites/totalSprites);
    
    // Load the next piece after a brief pause to allow for the UI to update.
    if (m_LoadingData.colomn < m_LoadingData.gridWidth)
    {
        runAction(CCSequence::create(CCDelayTime::create(1.0f / 60),
                                     CCCallFunc::create(this, callfunc_selector(CompositeSprite::loadNextPiece)),
                                     NULL));
    }
    
    // End the loading cycle and inform all observers.
    else
    {
        for (int i = 0; i < m_Observers.size(); i++)
        {
            m_Observers[i]->compositeSpriteFinishedLoading(this);
        }
        m_LoadingData.loadingPopup->closePopup();
        CCLOG("Finished loading CompositeSprite.");
    }
}
