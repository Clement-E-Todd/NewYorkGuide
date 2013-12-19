//
//  Defines.h
//  New York Guide
//
//  Created by Clément Todd on 2013-12-08.
//
//

#ifndef DEFINES_H
#define DEFINES_H

/**
 * A quick reference to CCDirector's getWinSize() method.
 */
#define WIN_SIZE cocos2d::CCDirector::sharedDirector()->getWinSize()

/**
 * Whether or not messages related to touch input should be displayed in the console.
 */
#define DISPLAY_TOUCH_MESSAGES false

/**
 *  The scale of the screen compared to iPad Retina (ie. iPad Retina would be "1" while non-retina would be "0.5")
 */
#define SCREEN_SCALE (WIN_SIZE.width / 1536)

#endif // DEFINES_H
