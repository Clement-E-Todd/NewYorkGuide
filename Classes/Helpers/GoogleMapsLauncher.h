//
//  GoogleMapsLauncher.h
//  NewYorkGuide
//
//  Created by Clement Todd on 2014-01-05.
//
//

#ifndef GOOGLE_MAPS_LAUNCHER_H
#define GOOGLE_MAPS_LAUNCHER_H

class GoogleMapsLauncher
{
public:
    
    /**
     @brief     Launch map with URL. This method will first try to launch the map using the Google Maps app and if that fails, it will attempt to launch Google Maps in a browser.
     @param     The URL to display.
     */
    static void launchWithURL(const char* mapURL);
    
    /**
     @brief     Shows directions to a specified destination.
     @param     The destination.
     */
    static void showDirections(const char* destination);
    
private:
    
    /**
     @brief     Default constructor. Declared as private because this class is not meant to be instantiated.
     */
    GoogleMapsLauncher() { }
};

#endif // GOOGLE_MAPS_LAUNCHER_H
