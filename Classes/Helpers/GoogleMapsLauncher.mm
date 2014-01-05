//
//  GoogleMapsLauncher.cpp
//  NewYorkGuide
//
//  Created by Clement Todd on 2014-01-05.
//
//

#include "GoogleMapsLauncher.h"
#import <GoogleMaps/GoogleMaps.h>

#include "cocos2d.h"
using namespace cocos2d;

/**
 @brief     Launch map with URL. This method will first try to launch the map using the Google Maps app and if that fails, it will attempt to launch Google Maps in a browser.
 @param     The URL to display.
 */
void GoogleMapsLauncher::launchWithURL(const char* mapURL)
{
    // Attempt to launch the map using the Google Maps iOS app.
    CCLOG("Attempting to display \"%s\" in Google Maps app...", mapURL);
    if ([[UIApplication sharedApplication] canOpenURL: [NSURL URLWithString:@"comgooglemaps://"]])
    {
        char fullURL[256];
        sprintf(fullURL, "comgooglemaps://?%s", mapURL);
        
        [[UIApplication sharedApplication] openURL: [NSURL URLWithString:[NSString stringWithUTF8String:fullURL]]];
        
        CCLOG("Google Maps app succeeded!");
    }
    
    // If the launch failed, attempt to display to map in-browser instead.
    else
    {
        char fullURL[256];
        sprintf(fullURL, "https://maps.google.com/maps?%s", mapURL);
        
        NSURL* nsURL = [NSURL URLWithString:[NSString stringWithUTF8String:fullURL]];
        
        CCLOG("Google Maps app failed. Attempting to display in browser instead...");
        if ([[UIApplication sharedApplication] canOpenURL:nsURL])
        {
            [[UIApplication sharedApplication] openURL: nsURL];
            CCLOG("In-browser map succeeded!");
        }
        else
        {
            CCLOG("In-browser map failed.");
        }
    }
}

/**
 @brief     Shows directions to a specified destination.
 @param     The destination.
 */
void GoogleMapsLauncher::showDirections(const char* destination)
{
    char destinationURL[256];
    sprintf(destinationURL, "daddr=%s", destination);
    launchWithURL(destinationURL);
}