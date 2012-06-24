//
//  PRFilledPolygon.cpp
//  cutcutcut
//
//  Created by Hanno Bruns on 23.06.12.
//  Copyright (c) 2012 zeiteisens. All rights reserved.
//

#include "PRFilledPolygon.h"

using namespace cocos2d;

PRFilledPolygon::PRFilledPolygon(void)
{
    
}

PRFilledPolygon::~PRFilledPolygon(void)
{
    free(areaTrianglePoints);
    free(textureCoordinates);
    delete _texture;    
}

bool PRFilledPolygon::init(void)
{
    return true;
}

/**
 Returns an autoreleased polygon.  Default triangulator is used (Ratcliff's).
 */
PRFilledPolygon* PRFilledPolygon::filledPolygonWithPoints(std::vector<cocos2d::CCPoint> polygonPoints, CCTexture2D *fillTexture)
{
    PRFilledPolygon *pobPRFilledPolygon = new PRFilledPolygon();
    if (pobPRFilledPolygon && pobPRFilledPolygon->initWithPoints(polygonPoints, fillTexture))
    {
        pobPRFilledPolygon->autorelease();
        return pobPRFilledPolygon;
    }
    CC_SAFE_DELETE(pobPRFilledPolygon);
    return NULL;
}

bool PRFilledPolygon::initWithPoints(std::vector<cocos2d::CCPoint> polygonPoints, CCTexture2D *fillTexture)
{
    CCGLProgram *shaderProgram = this->getShaderProgram();
    shaderProgram = CCShaderCache::sharedShaderCache()->programForKey(kCCShader_PositionTexture);
    setTexture(fillTexture);
    setPoints(polygonPoints);
    return true;
}

void PRFilledPolygon::setPoints(std::vector<cocos2d::CCPoint> points)
{
    if (areaTrianglePoints)
        free(areaTrianglePoints);
    if (textureCoordinates)
        free(textureCoordinates);
    Vector2dVector inputPoints;
    for (int i = 0; i < points.size(); i++) 
    {
        CCPoint point = points[i];
        Vector2d *vector = new Vector2d(point.x, point.y);
        inputPoints.push_back(*vector);
    }
    
    Vector2dVector triangulatedPoints;
    Triangulate::Process(inputPoints, triangulatedPoints);
    // is there a leak?
//    for (int i = 0; i < inputPoints.size(); i++) 
//    {
//        Vector2d *vector = &inputPoints[i];
//        delete vector;
//    }
    areaTrianglePointCount = triangulatedPoints.size();
    areaTrianglePoints = (CCPoint *)malloc(sizeof(CCPoint) * areaTrianglePointCount);
    textureCoordinates = (CCPoint *)malloc(sizeof(CCPoint) * areaTrianglePointCount);
    
    for (int i = 0; i < areaTrianglePointCount; i++)
    {
        Vector2d vector = triangulatedPoints[i];
        float x = vector.GetX();
        float y = vector.GetY();
        areaTrianglePoints[i] = ccp(x, y);
    }
    calculateTextureCoordinates();
}

void PRFilledPolygon::calculateTextureCoordinates()
{
    for (int j = 0; j < areaTrianglePointCount; j++) 
    {
        textureCoordinates[j] = ccpMult(areaTrianglePoints[j], 1.0f/_texture->getPixelsWide()*CC_CONTENT_SCALE_FACTOR());
        textureCoordinates[j].y = 1 - textureCoordinates[j].y;
    }
}

void PRFilledPolygon::draw(void)
{
     CC_NODE_DRAW_SETUP();
     
     ccGLBindTexture2D( _texture->getName() );
     
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
     
     ccGLBlendFunc( _blendFunc.src, _blendFunc.dst);
     
     ccGLEnableVertexAttribs( kCCVertexAttribFlag_Position | kCCVertexAttribFlag_TexCoords );
     
     glVertexAttribPointer(kCCVertexAttrib_Position, 2, GL_FLOAT, GL_FALSE, 0, areaTrianglePoints);
     glVertexAttribPointer(kCCVertexAttrib_TexCoords, 2, GL_FLOAT, GL_FALSE, 0, textureCoordinates);
     
     glDrawArrays(GL_TRIANGLES, 0, areaTrianglePointCount);
}

ccBlendFunc PRFilledPolygon::getBlendFunc()
{
    return _blendFunc;
}

void PRFilledPolygon::setBlendFunc(ccBlendFunc var)
{
    _blendFunc = var;
}

CCTexture2D* PRFilledPolygon::getTexture()
{
    return _texture;
}

void PRFilledPolygon::setTexture(CCTexture2D *var)
{
    if (_texture != var)
    {
        CC_SAFE_RETAIN(var);
        CC_SAFE_RELEASE(_texture);
        _texture = var;
        updateBlendFunc();
        ccTexParams texParams = { GL_NEAREST, GL_NEAREST, GL_REPEAT, GL_REPEAT };
        _texture->setTexParameters(&texParams);
        calculateTextureCoordinates();
    }
}

void PRFilledPolygon::updateBlendFunc()
{
    if (!_texture || _texture->getHasPremultipliedAlpha())
    {
        _blendFunc.src = GL_SRC_ALPHA;
        _blendFunc.dst = GL_ONE_MINUS_SRC_ALPHA;
    }
    else 
    {
        _blendFunc.src = CC_BLEND_SRC;
        _blendFunc.dst = CC_BLEND_DST;
    }
}