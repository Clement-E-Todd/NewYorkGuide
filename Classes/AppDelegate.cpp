//
//  AppDelegate.cpp
//  New York Guide
//
//  Created by Clément Todd on 2013-12-08.
//  Copyright Clément Todd 2013. All rights reserved.
//

#include "AppDelegate.h"

#include "cocos2d.h"
#include "NYGScene.h"

USING_NS_CC;

AppDelegate::AppDelegate()
{
}

AppDelegate::~AppDelegate()
{
}

bool AppDelegate::applicationDidFinishLaunching()
{
    // Initialize cocos2d-x's "CCDirector".
    CCDirector *pDirector = CCDirector::sharedDirector();
    pDirector->setOpenGLView(CCEGLView::sharedOpenGLView());
    
    // Create the app's scene and run it.
    CCScene *pScene = NewYorkGuide::scene();
    pDirector->runWithScene(pScene);

    return true;
}

void AppDelegate::applicationDidEnterBackground()
{
    // Pause "CCDirector" when the app loses focus.
    CCDirector::sharedDirector()->pause();
}

void AppDelegate::applicationWillEnterForeground()
{
    // Resume "CCDirector" when the app gains focus.
    CCDirector::sharedDirector()->resume();
}
