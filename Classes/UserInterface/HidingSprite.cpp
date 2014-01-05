//
//  HidingSprite.cpp
//  NewYorkGuide
//
//  Created by Clement Todd on 2014-01-05.
//
//

#include "HidingSprite.h"
#include "Defines.h"

using namespace cocos2d;

HidingSprite* HidingSprite::createWithTexture(CCTexture2D *pTexture)
{
    HidingSprite *pobSprite = new HidingSprite();
    if (pobSprite && pobSprite->initWithTexture(pTexture))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

HidingSprite* HidingSprite::createWithTexture(CCTexture2D *pTexture, const CCRect& rect)
{
    HidingSprite *pobSprite = new HidingSprite();
    if (pobSprite && pobSprite->initWithTexture(pTexture, rect))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

HidingSprite* HidingSprite::create(const char *pszFileName)
{
    HidingSprite *pobSprite = new HidingSprite();
    if (pobSprite && pobSprite->initWithFile(pszFileName))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

HidingSprite* HidingSprite::create(const char *pszFileName, const CCRect& rect)
{
    HidingSprite *pobSprite = new HidingSprite();
    if (pobSprite && pobSprite->initWithFile(pszFileName, rect))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

HidingSprite* HidingSprite::createWithSpriteFrame(CCSpriteFrame *pSpriteFrame)
{
    HidingSprite *pobSprite = new HidingSprite();
    if (pSpriteFrame && pobSprite && pobSprite->initWithSpriteFrame(pSpriteFrame))
    {
        pobSprite->autorelease();
        return pobSprite;
    }
    CC_SAFE_DELETE(pobSprite);
    return NULL;
}

HidingSprite* HidingSprite::createWithSpriteFrameName(const char *pszSpriteFrameName)
{
    CCSpriteFrame *pFrame = CCSpriteFrameCache::sharedSpriteFrameCache()->spriteFrameByName(pszSpriteFrameName);
    
#if COCOS2D_DEBUG > 0
    char msg[256] = {0};
    sprintf(msg, "Invalid spriteFrameName: %s", pszSpriteFrameName);
    CCAssert(pFrame != NULL, msg);
#endif
    
    return createWithSpriteFrame(pFrame);
}

HidingSprite* HidingSprite::create()
{
    HidingSprite *pSprite = new HidingSprite();
    if (pSprite && pSprite->init())
    {
        pSprite->autorelease();
        return pSprite;
    }
    CC_SAFE_DELETE(pSprite);
    return NULL;
}

/**
 * Visits this node's children and draw them recursively. If this sprite is off-screen, this method will be skipped.
 */
void HidingSprite::visit(void)
{
    CCPoint min = convertToWorldSpace(CCPointZero);
    CCPoint max = convertToWorldSpace(ccp(getContentSize().width, getContentSize().height));
    
    if (min.x > WIN_SIZE.width ||
        min.y > WIN_SIZE.height ||
        max.x < 0 ||
        max.y < 0)
    {
        return;
    }
    
    CCNode::visit();
}
