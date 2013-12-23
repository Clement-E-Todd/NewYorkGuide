//
//  NewYorkMap.cpp
//  NewYorkGuide
//
//  Created by Clement Todd on 2013-12-22.
//
//

#include "NewYorkMap.h"
#include "CompositeSprite.h"

/**
 @brief     Create a NewYorkMap instance.
 @return    A pointer to the newly created NewYorkMap.
 */
NewYorkMap* NewYorkMap::create()
{
    NewYorkMap *map = new NewYorkMap();
    if (map && map->init())
    {
        map->autorelease();
        return map;
    }
    CC_SAFE_DELETE(map);
    return NULL;
}

/**
 @brief     Initialize this NewYorkMap instance.
 @return    Whether or not initialization succeeded.
 */
bool NewYorkMap::init()
{
    if (!Map::init(CompositeSprite::create("newYorkMap", ".png", 4, 5)))
    {
        return false;
    }
    
    // Add the landmarks to the map.
    
    addLandmark(Landmark("Madison Square Garden",
                         "madisonSquareGarden.jpeg",
                         "A brief description of the landmark.",
                         ""),
                ccp(0.425f, 0.64f));
    
    addLandmark(Landmark("Statue of Liberty",
                         "statueOfLiberty.png",
                         "A brief description of the landmark.",
                         ""),
                ccp(0.07f, 0.05f));
    
    addLandmark(Landmark("Ellis Island",
                         "ellisIsland.jpg",
                         "A brief description of the landmark.",
                         ""),
                ccp(0.07f, 0.2f));
    
    addLandmark(Landmark("9/11 Memorial",
                         "911memorial.png",
                         "A brief description of the landmark.",
                         ""),
                ccp(0.28f, 0.24f));
    
    addLandmark(Landmark("Wall Street",
                         "wallStreet.jpg",
                         "A brief description of the landmark.",
                         ""),
                ccp(0.385f, 0.14f));
    
    addLandmark(Landmark("Battery Park",
                         "batteryPark.jpg",
                         "A brief description of the landmark.",
                         ""),
                ccp(0.245f, 0.14f));
    
    addLandmark(Landmark("World Financial Centre",
                         "worldFinancialCentre.jpg",
                         "A brief description of the landmark.",
                         ""),
                ccp(0.28f, 0.34f));
    
    addLandmark(Landmark("Brooklyn Bridge",
                         "brooklynBridge.jpg",
                         "A brief description of the landmark.",
                         ""),
                ccp(0.55f, 0.1f));
    
    addLandmark(Landmark("China Town",
                         "chinaTown.jpg",
                         "A brief description of the landmark.",
                         ""),
                ccp(0.44f, 0.31f));
    
    addLandmark(Landmark("East River Park",
                         "eastRiverPark.jpg",
                         "A brief description of the landmark.",
                         ""),
                ccp(0.775f, 0.31f));
    
    addLandmark(Landmark("Saint Patrick's Old Catherdral",
                         "stPatricksOldCathedral.jpg",
                         "A brief description of the landmark.",
                         ""),
                ccp(0.54f, 0.41f));
    
    addLandmark(Landmark("Flatiron Building",
                         "flatironBuilding.jpg",
                         "A brief description of the landmark.",
                         ""),
                ccp(0.475f, 0.54f));
    
    addLandmark(Landmark("Empire State Building",
                         "empireStateBuilding.jpg",
                         "A brief description of the landmark.",
                         ""),
                ccp(0.565f, 0.64f));
    
    addLandmark(Landmark("Chrysler Building",
                         "chryslerBuilding.jpg",
                         "A brief description of the landmark.",
                         ""),
                ccp(0.705f, 0.64f));
    
    addLandmark(Landmark("United Nations Headquarters",
                         "unitedNationsHeadquarters.gif",
                         "A brief description of the landmark.",
                         ""),
                ccp(0.845f, 0.59f));
    
    addLandmark(Landmark("Times Square",
                         "timesSquare.jpg",
                         "A brief description of the landmark.",
                         ""),
                ccp(0.46f, 0.7f));
    
    addLandmark(Landmark("Rockefeller Center",
                         "rockefellerCenter.jpg",
                         "A brief description of the landmark.",
                         ""),
                ccp(0.53f, 0.71f));
    
    addLandmark(Landmark("Carnegie Hall",
                         "carnegieHall.jpg",
                         "A brief description of the landmark.",
                         ""),
                ccp(0.53f, 0.77f));
    
    addLandmark(Landmark("Broadway",
                         "broadway.JPG",
                         "A brief description of the landmark.",
                         ""),
                ccp(0.485f, 0.85f));
    
    addLandmark(Landmark("The Metropolitan Opera House",
                         "metropolitanOperaHouse.jpg",
                         "A brief description of the landmark.",
                         ""),
                ccp(0.5f, 0.92f));
    
    addLandmark(Landmark("Strawberry Fields",
                         "strawberryFields.jpg",
                         "A brief description of the landmark.",
                         ""),
                ccp(0.62f, 0.91f));
    
    addLandmark(Landmark("Central Park",
                         "centralPark.jpg",
                         "A brief description of the landmark.",
                         ""),
                ccp(0.7f, 0.975f));
    
    addLandmark(Landmark("Metropolitan Museum of Art",
                         "metropolitanMuseumOfArt.jpg",
                         "A brief description of the landmark.",
                         ""),
                ccp(0.77f, 0.96f));
    
    addLandmark(Landmark("Guggenheim Museum",
                         "guggenheimMuseum.jpg",
                         "A brief description of the landmark.",
                         ""),
                ccp(0.91f, 0.94f));
    
    return true;
}
