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
    
    /**
     @brief     Default consructor which sets no data.
     */
    Landmark() { }
    
    /**
     @brief     Constructor
     @param     name            The landmark's title.
     @param     imageFileName   The file name of the image representing this landmark.
     @param     description     A brief description of the landmark.
     */
    Landmark(const char* name,
             const char* imageFileName,
             const char* description)
    {
        this->name = name;
        this->imageFileName = imageFileName;
        this->description = description;
    }
};

#endif // LANDMARK_H
