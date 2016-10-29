#ifndef BLUEBIRD_H
#define BLUEBIRD_H

#include "gameitem.h"
#include "bird.h"

class Bluebird:public Bird
{
    public:
        Bluebird(float x, float y, float r, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);

        virtual void SpecialSkill();

        b2BodyDef bodydef;

        int radius;
};

#endif // WHITEBIRD_H
