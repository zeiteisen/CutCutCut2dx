//
//  Watermelon.cpp
//  cutcutcut
//
//  Created by Hanno Bruns on 24.06.12.
//  Copyright (c) 2012 zeiteisens. All rights reserved.
//

#include "Watermelon.h"

using namespace cocos2d;

Watermelon::Watermelon()
{

}

Watermelon::~Watermelon()
{
    
}

Watermelon* Watermelon::spriteWithWorld(b2World *world)
{
    Watermelon *pobWatermelon = new Watermelon();
    if (pobWatermelon && pobWatermelon->initWithWorld(world))
    {
        pobWatermelon->autorelease();
        return pobWatermelon;
    }
    CC_SAFE_DELETE(pobWatermelon);
    return NULL;
}

bool Watermelon::initWithWorld(b2World *world)
{
    int32 count = 7;
    string file = "watermelon.png";
    b2Vec2 vertices[] = {
        b2Vec2(5.0/PTM_RATIO,15.0/PTM_RATIO),
        b2Vec2(18.0/PTM_RATIO,7.0/PTM_RATIO),
        b2Vec2(32.0/PTM_RATIO,5.0/PTM_RATIO),
        b2Vec2(48.0/PTM_RATIO,7.0/PTM_RATIO),
        b2Vec2(60.0/PTM_RATIO,14.0/PTM_RATIO),
        b2Vec2(34.0/PTM_RATIO,59.0/PTM_RATIO),
        b2Vec2(28.0/PTM_RATIO,59.0/PTM_RATIO)
    };
    CCSize screen = CCDirector::sharedDirector()->getWinSize();
    
    b2Body *body = createBodyForWorld(world, b2Vec2(screen.width/2/PTM_RATIO, screen.height/2/PTM_RATIO), 0, vertices, count, 5.0, .2, .2);
    
    PolygonSprite::initWithFile(file, body, true);
    return true;
}