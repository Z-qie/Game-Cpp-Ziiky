#pragma once

#include "Utils.h"
#include "DisplayableObject.h"
#include "Zy21586Engine.h"
#include "ImageMappingGeneralist.h"

//All game objects inherit from DisplayableObject class and will be contained and handled in the DisplayableObjectContainer. 
//Each game object is enhanced with a sprite and ImageMappingGeneralist(see below), which can display image with rotation, translation
//and color Manipulation. Each GameObject uses center as coordinate and saved as Vec2 by default
class GameObject : public DisplayableObject
{
protected:
    double m_dAngle{ 0.0 };
    SimpleImage sprite;
    ImageMappingGeneralist* m_pSpriteMapping{ nullptr };

public:
    explicit GameObject(int iWidth = 0, int iHeight = 0, int iStartX = 0, int iStartY = 0, bool useTopLeft00 = false)
        :DisplayableObject(iStartX, iStartY, Zy21586Engine::getInstance(), iWidth, iHeight, useTopLeft00)
        , m_pSpriteMapping(new ImageMappingGeneralist(0/*rotation*/, getPosition().x, getPosition().y))
    {};

    virtual ~GameObject() {
        delete m_pSpriteMapping;
    };

    virtual void virtStart() {}; 
    virtual void drawSprite() {};

    inline Vec2 getPosition() const {
        return Vec2{ m_iCurrentScreenX, m_iCurrentScreenY };
    };

    inline Vec2 getDrawStartPoint() const {
        return Vec2{ m_iCurrentScreenX + m_iStartDrawPosX, m_iCurrentScreenY + m_iStartDrawPosY };
    };

    //set position by target as center-ed coordinate instead of by top left 00
    inline void setPosition(const Vec2& target) {
        m_iCurrentScreenX = target.x;
        m_iCurrentScreenY = target.y;
    }

    inline void setAngle(double angle) {
        m_dAngle = angle;
    }

    inline double getAngle() {
        return m_dAngle;
    }

    inline void translatePositionBy(const Vec2& delta) {
        m_iCurrentScreenX += delta.x;
        m_iCurrentScreenY += delta.y;
    };

};

