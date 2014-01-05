//
//  WebLauncher.h
//  NewYorkGuide
//
//  Created by Clement Todd on 2014-01-01.
//
//

#ifndef WEB_LAUNCHER_H
#define WEB_LAUNCHER_H

/**
 @brief     A helper class which makes it easy to launch a web browser.
 */
class WebLauncher
{
public:
    
    /**
     @brief     Launch a web browser and open a website based on a specified URL.
     @param     webURL      The address of the website which should be opened.
     */
    static void launchBrowserWithURL(const char* url);
    
};

#endif // WEB_LAUNCHER_H