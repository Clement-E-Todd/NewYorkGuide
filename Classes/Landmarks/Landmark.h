//
//  Landmark.h
//  NewYorkGuide
//
//  Created by Clement Todd on 2013-12-22.
//
//

#ifndef LANDMARK_H
#define LANDMARK_H

/**
 @brief     A structure containing all of the information to be presented to the user regarding a landmark.
 */
struct Landmark
{
    /** The landmark's title. */
    const char* name;
    
    /** The file name of the image representing this landmark. */
    const char* imageFileName;
    
    /** A brief description of the landmark. */
    const char* description;
    
    /** An address to be used by the Google Maps SDK in order to show directions to this landmark. */
    const char* address;
    
    /** The URL of the landmark's website (optional, set to "" for none). */
    const char* websiteURL;
    
    /** The URL for buying tickets to the landmark if applicable (also optional). */
    const char* ticketsURL;
    
    /**
     @brief     Default consructor which sets no data.
     */
    Landmark() { }
    
    /**
     @brief     Constructor
     @param     name            The landmark's title.
     @param     imageFileName   The file name of the image representing this landmark.
     @param     description     A brief description of the landmark.
     @param     address         An address to be used by the Google Maps SDK in order to show directions to this landmark.
     @param     websiteURL      The URL of the landmark's website (optional, set to "" for none).
     @param     ticketsURL      The URL for buying tickets to the landmark if applicable (also optional).
     */
    Landmark(const char* name,
             const char* imageFileName,
             const char* description,
             const char* address = NULL,
             const char* websiteURL = NULL,
             const char* ticketsURL = NULL)
    {
        this->name = name;
        this->imageFileName = imageFileName;
        this->description = description;
        this->address = address;
        this->websiteURL = websiteURL;
        this->ticketsURL = ticketsURL;
    }
};

#endif // LANDMARK_H
