//
//  AppController.h
//  New York Guide
//
//  Created by Clément Todd on 2013-12-08.
//  Copyright Clément Todd 2013. All rights reserved.
//

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
}

@end

