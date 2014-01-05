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
    
    addLandmark(Landmark("Madison\nSquare Garden",
                         "madisonSquareGarden",
                         "An indoor, mutli-purpose arena\nas well as New York's oldest and\nbusiest sporting venue.",
                         "Madison+Square+Garden+NYC",
                         "http://www.thegarden.com/",
                         "http://www.thegarden.com/calendar"),
                ccp(0.425f, 0.64f));
    
    addLandmark(Landmark("Statue of Liberty",
                         "statueOfLiberty",
                         "A colossal monument in the image\nof Libertas, the Roman godess of\nfreedom. This statue was a gift from\nFrance and represents the idea\nof American liberty.",
                         "Statue+of+Liberty+NYC",
                         "http://www.statueofliberty.org/",
                         "https://www.statueoflibertytickets.com/"),
                ccp(0.07f, 0.05f));
    
    addLandmark(Landmark("Ellis Island",
                         "ellisIsland",
                         "Once America's busiest immigration\ninspection station, Ellis Island is now\npart of the Statue of Liberty momument\nand hosts an immigration museum.",
                         "Ellis+Island+NYC",
                         "https://www.ellisisland.org/",
                         "http://www.statueoflibertytickets.com/Ellis-Island-Tour/"),
                ccp(0.07f, 0.2f));
    
    addLandmark(Landmark("9/11 Memorial",
                         "911memorial",
                         "A national tribute to the men, women\nand children killed in the terrorist\nattacks of 2001 and 1993.",
                         "9+11+Memorial+NYC",
                         "http://www.911memorial.org/"),
                ccp(0.28f, 0.24f));
    
    addLandmark(Landmark("Wall Street",
                         "wallStreet",
                         "Stretching from Broadway to\nSouth Street on the East River,\nWall Street is the financial district\nof New York City and home to the\nNew York Stock Exchange.",
                         "Wall+Street+NYC"),
                ccp(0.385f, 0.14f));
    
    addLandmark(Landmark("Battery Park",
                         "batteryPark",
                         "Decades before Ellis Island or the\nStatue of Liberty were built, Battery\nPark welcomed new immigrants from\naround the world.",
                         "Battery+Park+NYC",
                         "http://www.nycgovparks.org/parks/batterypark"),
                ccp(0.245f, 0.14f));
    
    addLandmark(Landmark("Brookfield Place",
                         "worldFinancialCentre",
                         "Formerly known as the \"World\nFinancial Center\", Brookfield Place is\na complex of towering office\nbuildings in Lower Manhattan.",
                         "Brookfield+Place+NYC",
                         "http://www.brookfieldplacenewsandevents.com/"),
                ccp(0.28f, 0.34f));
    
    addLandmark(Landmark("Brooklyn nBridge",
                         "brooklynBridge",
                         "Spanning the East River and connecting\nBrooklyn to the boroughs of Manhattan,\nthe Brooklyn Bridge is one of the\noldest suspension bridges\nin the country.",
                         "Brooklyn+Bridge+NYC"),
                ccp(0.55f, 0.1f));
    
    addLandmark(Landmark("Chinatown",
                         "chinaTown",
                         "Chinatown is home to the largest\nenclave of Chinese people in the\nWestern Hemisphere as well as one\nof the largest Chinese populations.",
                         "Chinatown+NYC",
                         "http://www.explorechinatown.com/"),
                ccp(0.44f, 0.31f));
    
    addLandmark(Landmark("East River Park",
                         "eastRiverPark",
                         "A 57.5-acre park stretching along the\nEast River which features an\namphitheater, numerous sports\ncourts and bike paths as well as\nother attractions.",
                         "East+River+Park+NYC",
                         "http://www.nycgovparks.org/parks/eastriverpark"),
                ccp(0.775f, 0.31f));
    
    addLandmark(Landmark("Saint Patrick's\nOld Catherdral",
                         "stPatricksOldCathedral",
                         "The Basilica of St. Patrick's Old\nCathedral is an historic\nlandmark Catholic Church\nand cemetery.",
                         "St+Patricks+Old+Cathedral+NYC"),
                ccp(0.54f, 0.41f));
    
    addLandmark(Landmark("Flatiron\nBuilding",
                         "flatironBuilding",
                         "The Flatiron Building, originally\nthe Fuller Building, is\nconsidered to be a\ngroundbreaking skyscraper.",
                         "Flatiron+Building+NYC"),
                ccp(0.475f, 0.54f));
    
    addLandmark(Landmark("Empire State\nBuilding",
                         "empireStateBuilding",
                         "The Empire State Building is a\n103-story skyscraper located\nin Midtown Manhattan",
                         "Empire+State+Building+NYC"),
                ccp(0.565f, 0.64f));
    
    addLandmark(Landmark("Chrysler\nBuilding",
                         "chryslerBuilding",
                         "The Chrysler Building is an Art\nDeco style skyscraper in\nNew York City.",
                         "Chrysler+Building+NYC"),
                ccp(0.705f, 0.64f));
    
    addLandmark(Landmark("United Nations\nHeadquarters",
                         "unitedNationsHeadquarters",
                         "The headquarters of the United\nNations is a complex in\nNew York City.",
                         "United+Nations+Headquarters+NYC",
                         "http://www.un.org/cyberschoolbus/untour/subunh.htm"),
                ccp(0.845f, 0.59f));
    
    addLandmark(Landmark("Times Square",
                         "timesSquare",
                         "Times Square is a major commercial\nintersection in Midtown Manhattan\nat the junction of Broadway and\nSeventh Avenue, stretching from\nWest 42nd to West 47th Streets.",
                         "Times+Square+NYC",
                         "http://www.timessquarenyc.org/"),
                ccp(0.46f, 0.7f));
    
    addLandmark(Landmark("Rockefeller\nCenter",
                         "rockefellerCenter",
                         "Rockefeller Center is a complex of 19\ncommercial buildings covering\n22 acres between 48th and 51st\nstreets in New York City",
                         "Rockefeller+Center+NYC",
                         "http://www.rockefellercenter.com/"),
                ccp(0.53f, 0.71f));
    
    addLandmark(Landmark("Carnegie Hall",
                         "carnegieHall",
                         "A concert venue in Midtown Manhattan,\nit is one of the most prestigious\nvenues in the world for both\nclassical music and\npopular music.",
                         "Carnegie+Hall+NYC",
                         "http://www.carnegiehall.org/‎",
                         "http://www.carnegiehall.org/Calendar/"),
                ccp(0.53f, 0.77f));
    
    addLandmark(Landmark("Broadway",
                         "broadway",
                         "A collection of high-calibur,\nworld-famous theatres.",
                         "Broadway+NYC",
                         "", "http://www.broadway.com/"),
                ccp(0.485f, 0.85f));
    
    addLandmark(Landmark("The\nMetropolitan\nOpera House",
                         "metropolitanOperaHouse",
                         "Home to the Met, which is the\nlargest classical music\norganization in North America.",
                         "Metropolitan+Opera+NYC",
                         "www.metoperafamily.org/‎",
                         "https://www.metoperafamily.org/metopera/season/index.aspx"),
                ccp(0.5f, 0.92f));
    
    addLandmark(Landmark("Strawberry\nFields",
                         "strawberryFields",
                         "A section of Central Park dedicated to\nthe memory of Beatles member John\nLennon. It is named after the\n Beatles song \"Strawberry\nFields Forever\".",
                         "Central+Park+NYC",
                         "http://www.centralpark.com/guide/attractions/strawberry-fields.html"),
                ccp(0.62f, 0.91f));
    
    addLandmark(Landmark("Central Park",
                         "centralPark",
                         "Central Park is an urban park in the\neastern portion of the central-\nupper West Side of Manhattan in\nNew York City.",
                         "Central+Park+NYC",
                         "http://www.centralpark.com/‎"),
                ccp(0.7f, 0.975f));
    
    addLandmark(Landmark("Metropolitan\nMuseum of Art",
                         "metropolitanMuseumOfArt",
                         "The largest art museum in the\nUnited States, and one of the ten\nlargest in the world, with\nthe most significant\nart collections.",
                         "Metropolitan+Museum+of+Art+NYC",
                         "http://www.metmuseum.org/"),
                ccp(0.77f, 0.96f));
    
    addLandmark(Landmark("Guggenheim\nMuseum",
                         "guggenheimMuseum",
                         "The Guggenheim is a world-reknowned\nart museum located on the Upper East\nSide of Manhattan in New York City.",
                         "Guggenheim+NYC",
                         "http://www.guggenheim.org/"),
                ccp(0.91f, 0.94f));
    
    return true;
}
