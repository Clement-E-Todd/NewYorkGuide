//
//  Popup.cpp
//  NewYorkGuide
//
//  Created by Clement Todd on 2013-12-28.
//
//

#include "Popup.h"
#include "Defines.h"

using namespace cocos2d;

/**
 @brief     Create and add a popup to the current scene.
 @return    A pointer to the popup.
 */
Popup* Popup::showPopup()
{
    Popup* popup = create();
    
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

/**
 @brief     Create a new Popup instance.
 @return    A pointer to the newly created Popup.
 */
Popup* Popup::create()
{
    Popup *popup = new Popup();
    if (popup && popup->init())
    {
        popup->autorelease();
        return popup;
    }
    CC_SAFE_DELETE(popup);
    return NULL;
}

/**
 @brief     Initialize this Popup instance.
 @return    Whether or not initialization was successful.
 */
bool Popup::init()
{
    if (!CCNode::init())
    {
        return false;
    }
    
    // The popup will fill the screen, so set the content size to reflect that.
    setContentSize(WIN_SIZE);
    
    // Add a semi-transparent black backdrop
    CCSprite* backdrop = CCSprite::create("blankPixel.png");
    addChild(backdrop);
    backdrop->setAnchorPoint(CCPointZero);
    backdrop->cocos2d::CCNode::setScale(getContentSize().width, getContentSize().height);
    backdrop->setColor(ccBLACK);
    backdrop->setOpacity(220);
    
    // Register this popup with the touch dispatcher so that it can block input to elements behind it.
    CCDirector::sharedDirector()->getTouchDispatcher()->addTargetedDelegate(this, 0, true);
    
    return true;
}

/**
 @brief     Called when this is removed from the node tree.
 */
void Popup::onExit()
{
    // Unregister this Button from the touch dispatcher.
    CCDirector::sharedDirector()->getTouchDispatcher()->removeDelegate(this);
    
    // Pass the onExit() call along to the base class.
    CCNode::onExit();
}

/**
 @brief     Add a node to the popup. The node will be positioned automatically.
 */
void Popup::addContent(cocos2d::CCNode* content)
{
    addChild(content);
    m_Contents.push_back(content);
    organizeContent();
}

/**
 @brief     Add a button to the popup with specified text, callback and colour. The button will be positioned automatically.
 */
void Popup::addButton(const char* text, cocos2d::CCCallFunc* callback, cocos2d::ccColor3B colour)
{
    Button* button = Button::create("buttonNormal.png", "buttonPressed.png", NULL, callback);
    button->setColor(colour);
    button->setScale(SCREEN_SCALE);
    
    CCLabelTTF* label = CCLabelTTF::create(text, "Montserrat", 100);
    button->addChild(label);
    label->setPosition(ccp(button->getContentSize().width/2, button->getContentSize().height/2));
    
    addChild(button);
    m_Buttons.push_back(button);
    organizeContent();
}

/**
 @brief     Position all elements added to the popup in an evenly-spaced manner.
 */
void Popup::organizeContent()
{
    // Figure out the total height of all of the elements so that we can use it to find out how much spacing is needed between elements.
    float totalHeight = 0.0f;
    
    for (int i = 0; i < m_Contents.size(); i++)
    {
        totalHeight += m_Contents[i]->getContentSize().height * m_Contents[i]->getScaleY();
    }
    
    for (int i = 0; i < m_Buttons.size(); i++)
    {
        totalHeight += m_Buttons[i]->getContentSize().height * m_Buttons[i]->getScaleY();
    }
    
    // Calculate the spacing in between elements.
    float extraSpace = WIN_SIZE.height - totalHeight;
    float buffer = extraSpace / (m_Contents.size() + m_Buttons.size() + 3);
    
    // Position all of the normal contents
    for (int i = 0; i < m_Contents.size(); i++)
    {
        m_Contents[i]->setPositionX(WIN_SIZE.width/2 +
                                    (m_Contents[i]->getContentSize().width * m_Contents[i]->getScaleX() *
                                     (m_Contents[i]->getAnchorPoint().x - 0.5f)));
        
        float previousContentMinY = (i > 0) ? m_Contents[i-1]->getPositionY() -
                                                m_Contents[i-1]->getContentSize().height *
                                                m_Contents[i-1]->getScaleY() *
                                                m_Contents[i-1]->getAnchorPoint().y :
                                              WIN_SIZE.height;
        
        m_Contents[i]->setPositionY(previousContentMinY - buffer -
                                    (m_Contents[i]->getContentSize().height *
                                     m_Contents[i]->getScaleY() *
                                     (1 - m_Contents[i]->getAnchorPoint().y)));
    }
    
    // Position all of the buttons
    for (int i = 0; i < m_Buttons.size(); i++)
    {
        m_Buttons[i]->setPositionX(WIN_SIZE.width/2 +
                                   (m_Buttons[i]->getContentSize().width *
                                    m_Buttons[i]->getScaleX() *
                                    (m_Buttons[i]->getAnchorPoint().x - 0.5f)));
        
        float previousButtonMinY;
        
        if (i > 0)
        {
            previousButtonMinY = m_Buttons[i-1]->getPositionY() -
                                   m_Buttons[i-1]->getContentSize().height *
                                   m_Buttons[i-1]->getScaleY() *
                                   m_Buttons[i-1]->getAnchorPoint().y;
        }
        else
        {
            float contentMinY = (m_Contents.size() > 0) ? m_Contents[m_Contents.size()-1]->getPositionY() -
            m_Contents[m_Contents.size()-1]->getContentSize().height *
            m_Contents[m_Contents.size()-1]->getScaleY() *
            m_Contents[m_Contents.size()-1]->getAnchorPoint().y :
            WIN_SIZE.height/2;
            
            previousButtonMinY = contentMinY - buffer*2;
        }
        
        m_Buttons[i]->setPositionY(previousButtonMinY - buffer -
                                   (m_Buttons[i]->getContentSize().height *
                                    m_Buttons[i]->getScaleY() *
                                    (1 - m_Buttons[i]->getAnchorPoint().y)));
    }
}
