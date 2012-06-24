//
//  PolygonSprite.h
//  cutcutcut
//
//  Created by Hanno Bruns on 24.06.12.
//  Copyright (c) 2012 zeiteisens. All rights reserved.
//

#ifndef cutcutcut_PolygonSprite_h
#define cutcutcut_PolygonSprite_h

#include "PRFilledPolygon.h"
#include "cocos2d.h"
#include "Box2D.h"

#define PTM_RATIO 32

class PolygonSprite : public PRFilledPolygon
{
public:
    PolygonSprite(void);
    virtual ~PolygonSprite(void);
    
    static PolygonSprite* spriteWithFile(string filename, b2Body *body, bool original);
    static PolygonSprite* spriteWithTexture(cocos2d::CCTexture2D *texture, b2Body *body, bool original);
    static PolygonSprite* spriteWithWorld(b2World *world);
    bool initWithTexture(cocos2d::CCTexture2D *texture, b2Body *body, bool original);
    bool initWithFile(string filename, b2Body *body, bool original);
    virtual bool initWithWorld(b2World *world);
    b2Body* createBodyForWorld(b2World *world, b2Vec2 position, float rotation, b2Vec2 *vertices, int32 vertexCount, float density, float friction, float restitution);
    void activateCollisions();
    void deactivateCollisions();
    
    virtual void setPosition(cocos2d::CCPoint &position);
    virtual cocos2d::CCAffineTransform nodeToParentTransform(void);
    
private:
    CC_SYNTHESIZE(b2Body *, _body, Body);
    CC_SYNTHESIZE(bool, _original, Original);
    CC_SYNTHESIZE(b2Vec2, _centriod, Centriod);
};

#endif
