//
//  Watermelon.h
//  cutcutcut
//
//  Created by Hanno Bruns on 24.06.12.
//  Copyright (c) 2012 zeiteisens. All rights reserved.
//

#ifndef cutcutcut_Watermelon_h
#define cutcutcut_Watermelon_h

#include "PolygonSprite.h"

class Watermelon : public PolygonSprite
{
public:
    Watermelon(void);
    virtual ~Watermelon(void);
    static Watermelon* spriteWithWorld(b2World *world);
    virtual bool initWithWorld(b2World *world);
};

#endif
