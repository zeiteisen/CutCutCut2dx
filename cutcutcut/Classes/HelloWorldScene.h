//
//  HelloWorldScene.h
//  cutcutcut
//
//  Created by Hanno Bruns on 23.06.12.
//  Copyright zeiteisens 2012. All rights reserved.
//
#ifndef __HELLO_WORLD_H__
#define __HELLO_WORLD_H__

// When you import this file, you import all the cocos2d classes
#include "cocos2d.h"
#include "Box2D.h"

class HelloWorld : public cocos2d::CCLayer {
public:
    ~HelloWorld();
    HelloWorld();
    
    // returns a Scene that contains the HelloWorld as the only child
    static cocos2d::CCScene* scene();
    
    void initPhysics();
    // adds a new sprite at a given coordinate
    void addNewSpriteAtPosition(cocos2d::CCPoint p);

    virtual void draw();
    virtual void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);
    void update(cocos2d::ccTime dt);
    
private:
    b2World* world;
    CC_SYNTHESIZE(cocos2d::CCArray*, _cache, Cache);
    
    void initSprites();
};

#endif // __HELLO_WORLD_H__
