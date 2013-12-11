//
//  main.m
//  New York Guide
//
//  Created by Clément Todd on 2013-12-08.
//  Copyright Clément Todd 2013. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "AppController.h"

int main(int argc, char *argv[]) {
    
    NSAutoreleasePool * pool = [[NSAutoreleasePool alloc] init];
    int retVal = UIApplicationMain(argc, argv, nil, NSStringFromClass([AppController class]));
    [pool release];
    return retVal;
}
