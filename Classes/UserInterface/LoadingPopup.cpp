//
//  LoadingPopup.cpp
//  NewYorkGuide
//
//  Created by Clement Todd on 2014-01-05.
//
//

#include "LoadingPopup.h"

using namespace cocos2d;

// Create and add a popup to the current scene.

LoadingPopup* LoadingPopup::showPopup(cocos2d::CCSprite* borderSprite, ProgressBar* progressBar)
{
    LoadingPopup* popup = create(borderSprite, progressBar);
    
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

LoadingPopup* LoadingPopup::create(CCSprite* borderSprite, ProgressBar* progressBar)
{
    LoadingPopup *popup = new LoadingPopup();
    if (popup && popup->init(borderSprite, progressBar))
    {
        popup->autorelease();
        return popup;
    }
    CC_SAFE_DELETE(popup);
    return NULL;
}

// Initialize this Popup instance.

bool LoadingPopup::init(CCSprite* borderSprite, ProgressBar* progressBar)
{
    if (!Popup::init())
    {
        return false;
    }
    
    // Add the sprites
    m_ProgressBar = progressBar;
    addChild(m_ProgressBar);
    m_Border = borderSprite;
    addChild(m_Border);
    
    return true;
}

// Called when the node is removed fromt he node tree.

void LoadingPopup::onExit()
{
    CCTextureCache* cache = CCTextureCache::sharedTextureCache();
    cache->removeTexture(m_ProgressBar->getTexture());
    cache->removeTexture(m_Border->getTexture());
    
    Popup::onExit();
}

// Set the progress to be shown by the progress bar.

void LoadingPopup::setProgress(float progress)
{
    m_ProgressBar->setProgress(progress);
}

// Create a progress bar using a specified image file.

ProgressBar* ProgressBar::create(const char *fileName)
{
    ProgressBar *progressBar = new ProgressBar();
    if (progressBar && progressBar->initWithFile(fileName))
    {
        progressBar->autorelease();
        progressBar->m_Progress = 0.0f;
        return progressBar;
    }
    CC_SAFE_DELETE(progressBar);
    return NULL;
}

// Visits this node's children and draw them recursively. Progress bar clips a chunk based on the progress value.

void ProgressBar::visit(void)
{
    kmGLPushMatrix();
    
    glEnable(GL_SCISSOR_TEST);
    CCPoint worldPos = convertToWorldSpace(CCPointZero);
    CCEGLView::sharedOpenGLView()->setScissorInPoints(worldPos.x, worldPos.y,
                                                      getContentSize().width * m_Progress,
                                                      getContentSize().height);
    CCNode::visit();
    glDisable(GL_SCISSOR_TEST);
    kmGLPopMatrix();
}

// Set the progress to be shown by this sprite.

void ProgressBar::setProgress(float progress)
{
    m_Progress = progress;
}
