#ifndef NYG_SCENE_H
#define NYG_SCENE_H

#include "cocos2d.h"

/**
 @brief    The layer in which the application displays itself to the user.
 */

class NewYorkGuide : public cocos2d::CCLayer
{
public:
    
    /**
     @brief     Create a CCScene containing a NewYorkGuide layer.
     @return    A pointer to the newly created scene.
     */
    static cocos2d::CCScene* scene();
    
    
protected:
    
    /**
     @brief     Create an instance of the NewYorkGuide layer.
     @return    A pointer to the newly created layer.
     */
    CREATE_FUNC(NewYorkGuide);
    
    /**
     @brief     Initialize the layer by populating it with its contents.
     @return    true    The layer was initialized successfully.
     @return    false   The layer failed to initialize.
     */
    virtual bool init();
};

#endif // NYG_SCENE_H
