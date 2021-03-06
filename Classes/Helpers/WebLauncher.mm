//
//  WebLauncher.mm
//  NewYorkGuide
//
//  Created by Clement Todd on 2014-01-01.
//
//

#include "WebLauncher.h"

// Launch a web browser and open a website based on a specified URL.

void WebLauncher::launchBrowserWithURL(const char* url)
{
    NSURL *nsURL = [NSURL URLWithString:[NSString stringWithUTF8String:url]];
    
    if (![[UIApplication sharedApplication] openURL:nsURL])
        NSLog(@"Could not launch URL: %@",[nsURL description]);
}