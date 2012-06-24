//
//  PolygonSprite.cpp
//  cutcutcut
//
//  Created by Hanno Bruns on 24.06.12.
//  Copyright (c) 2012 zeiteisens. All rights reserved.
//

#include "PolygonSprite.h"

using namespace cocos2d;

PolygonSprite::PolygonSprite()
{
    
}

PolygonSprite::~PolygonSprite()
{
    
}

PolygonSprite* PolygonSprite::spriteWithFile(string filename, b2Body *body, bool original)
{
    PolygonSprite *pobPolygonSprite = new PolygonSprite();
    if (pobPolygonSprite && pobPolygonSprite->initWithFile(filename, body, original))
    {
        pobPolygonSprite->autorelease();
        return pobPolygonSprite;
    }
    CC_SAFE_DELETE(pobPolygonSprite);
    return NULL;
}

PolygonSprite* PolygonSprite::spriteWithTexture(CCTexture2D *texture, b2Body *body, bool original)
{
    PolygonSprite *pobPolygonSprite = new PolygonSprite();
    if (pobPolygonSprite && pobPolygonSprite->initWithTexture(texture, body, original))
    {
        pobPolygonSprite->autorelease();
        return pobPolygonSprite;
    }
    CC_SAFE_DELETE(pobPolygonSprite);
    return NULL;
}

PolygonSprite* PolygonSprite::spriteWithWorld(b2World *world)
{
    PolygonSprite *pobPolygonSprite = new PolygonSprite();
    if (pobPolygonSprite && pobPolygonSprite->initWithWorld(world))
    {
        pobPolygonSprite->autorelease();
        return pobPolygonSprite;
    }
    CC_SAFE_DELETE(pobPolygonSprite);
    return NULL;
}

bool PolygonSprite::initWithFile(string filename, b2Body *body, bool original)
{
    CCTexture2D *texture = CCTextureCache::sharedTextureCache()->addImage(filename.c_str());
    return initWithTexture(texture, body, original);
}

bool PolygonSprite::initWithTexture(cocos2d::CCTexture2D *texture, b2Body *body, bool original)
{
    b2Fixture *originalFixture = body->GetFixtureList();
    b2PolygonShape *shape = (b2PolygonShape*)originalFixture->GetShape();
    int vertextCount = shape->GetVertexCount();
    vector<CCPoint> points;
    for (int i = 0; i < vertextCount; i++)
    {
        CCPoint p = ccp(shape->GetVertex(i).x * PTM_RATIO, shape->GetVertex(i).y * PTM_RATIO);
        points.push_back(p);
    }
    PRFilledPolygon::initWithPoints(points, texture);
    _body = body;
    _body->SetUserData(this);
    _original = original;
    _centriod = _body->GetLocalCenter();
    this->setAnchorPoint(ccp(_centriod.x * PTM_RATIO / _texture->getContentSize().width, 
                             _centriod.y * PTM_RATIO / _texture->getContentSize().height));
    return true;
}

bool PolygonSprite::initWithWorld(b2World *world)
{
    return true;
}

void PolygonSprite::setPosition(cocos2d::CCPoint &position)
{
    CCNode::setPosition(position);
    _body->SetTransform(b2Vec2(position.x/PTM_RATIO, position.y*PTM_RATIO), _body->GetAngle());
}

b2Body* PolygonSprite::createBodyForWorld(b2World *world, b2Vec2 position, float rotation, b2Vec2 *vertices, int32 vertexCount, float density, float friction, float restitution)
{
    b2BodyDef bodyDef;
    bodyDef.type = b2_dynamicBody;
    bodyDef.position = position;
    bodyDef.angle = rotation;
    b2Body *body = world->CreateBody(&bodyDef);
    
    b2FixtureDef fixtureDef;
    fixtureDef.density = density;
    fixtureDef.friction = friction;
    fixtureDef.restitution = restitution;
    fixtureDef.filter.categoryBits = 0;
    fixtureDef.filter.maskBits = 0;
    
    b2PolygonShape shape;
    shape.Set(vertices, vertexCount);
    fixtureDef.shape = &shape;
    body->CreateFixture(&fixtureDef);
    
    return body;
}

void PolygonSprite::activateCollisions()
{
    b2Fixture *fixture = _body->GetFixtureList();
    b2Filter filter = fixture->GetFilterData();
    filter.categoryBits = 0x0001;
    filter.maskBits = 0x0001;
    fixture->SetFilterData(filter);
}

void PolygonSprite::deactivateCollisions()
{
    b2Fixture *fixture = _body->GetFixtureList();
    b2Filter filter = fixture->GetFilterData();
    filter.categoryBits = 0;
    filter.maskBits = 0;
    fixture->SetFilterData(filter);
}

CCAffineTransform PolygonSprite::nodeToParentTransform()
{    
    b2Vec2 pos  = _body->GetPosition();
    
    float x = pos.x * PTM_RATIO;
    float y = pos.y * PTM_RATIO;
    
    if ( !getIsRelativeAnchorPoint() ) {
        x += getAnchorPointInPoints().x;
        y += getAnchorPointInPoints().y;
    }
    
    // Make matrix
    float radians = _body->GetAngle();
    float c = cosf(radians);
    float s = sinf(radians);
    
    if( ! CCPoint::CCPointEqualToPoint(m_tAnchorPointInPoints, CCPointZero) ){
        x += c*-m_tAnchorPointInPoints.x+ -s*-m_tAnchorPointInPoints.y;
        y += s*-m_tAnchorPointInPoints.x+ c*-m_tAnchorPointInPoints.y;
    }
    
    // Rot, Translate Matrix
    m_tTransform = CCAffineTransformMake( c, s,
                                                        -s, c,
                                                        x, y);
    return m_tTransform;
}