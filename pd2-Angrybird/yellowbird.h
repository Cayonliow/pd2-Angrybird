#ifndef YELLOWBIRD_H
#define YELLOWBIRD_H

#include "gameitem.h"
#include "bird.h"

class Yellowbird:public Bird
{
public:
    Yellowbird(float x, float y, float r, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);

    b2BodyDef bodydef;

    virtual void SpecialSkill();
};

#endif // YELLOWBIRD_H
