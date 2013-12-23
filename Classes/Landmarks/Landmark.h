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
    // The landmark's title.
    const char* name;
    
    // The file name of the image representing this landmark.
    const char* imageFileName;
    
    // A brief description of the landmark.
    const char* description;
    
    // The URL of the lanmark's website (optional, set to "" for none).
    const char* websiteURL;
    
    /**
     @brief     Default consructor which sets no data.
     */
    Landmark() { }
    
    /**
     @brief     Constructor
     @param     name            The landmark's title.
     @param     imageFileName   The file name of the image representing this landmark.
     @param     description     A brief description of the landmark.
     @param     websiteURL      The URL of the lanmark's website (optional, set to "" for none).
     */
    Landmark(const char* name, const char* imageFileName, const char* description, const char* websiteURL)
    {
        this->name = name;
        this->imageFileName = imageFileName;
        this->description = description;
        this->websiteURL = websiteURL;
    }
};

#endif // LANDMARK_H
