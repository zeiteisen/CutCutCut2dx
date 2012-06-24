//
//  cutcutcutAppController.h
//  cutcutcut
//
//  Created by Hanno Bruns on 23.06.12.
//  Copyright zeiteisens 2012. All rights reserved.
//

@class RootViewController;

@interface AppController : NSObject <UIAccelerometerDelegate, UIAlertViewDelegate, UITextFieldDelegate,UIApplicationDelegate> {
    UIWindow *window;
    RootViewController    *viewController;
}

@end

