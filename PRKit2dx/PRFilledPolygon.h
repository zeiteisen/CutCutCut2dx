//
//  PRFilledPolygon.h
//  cutcutcut
//
//  Created by Hanno Bruns on 23.06.12.
//  Copyright (c) 2012 zeiteisens. All rights reserved.
//

#ifndef cutcutcut_PRFilledPolygon_h
#define cutcutcut_PRFilledPolygon_h

#include "cocos2d.h"
#include "triangulate.h"

class PRFilledPolygon : public cocos2d::CCNode
{
public:
    PRFilledPolygon(void);
    virtual ~PRFilledPolygon(void);
    virtual bool init(void);
    virtual void draw(void);
    
    static PRFilledPolygon* filledPolygonWithPoints(std::vector<cocos2d::CCPoint> polygonPoints, cocos2d::CCTexture2D *fillTexture);
    
    bool initWithPoints(std::vector<cocos2d::CCPoint>, cocos2d::CCTexture2D *fillTexture);
    void setPoints(std::vector<cocos2d::CCPoint>);
        
private:
    int areaTrianglePointCount;
    cocos2d::CCPoint *areaTrianglePoints;
    cocos2d::CCPoint *textureCoordinates;
    CC_PROPERTY(cocos2d::CCTexture2D *, _texture, Texture);
    CC_PROPERTY(cocos2d::ccBlendFunc, _blendFunc, BlendFunc);
    
    void calculateTextureCoordinates();
    void updateBlendFunc();
};

#endif
