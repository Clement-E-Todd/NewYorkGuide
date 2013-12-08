#include "NYGScene.h"
#include "SimpleAudioEngine.h"

using namespace cocos2d;
using namespace CocosDenshion;

CCScene* NewYorkGuide::scene()
{
    CCScene *scene = CCScene::create();
    NewYorkGuide *layer = NewYorkGuide::create();
    scene->addChild(layer);
    return scene;
}

bool NewYorkGuide::init()
{
    if ( !CCLayer::init() )
    {
        return false;
    }

    return true;
}
