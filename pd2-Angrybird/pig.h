#ifndef PIG_H
#define PIG_H

#include <QGraphicsScene>
#include <QTimer>
#include <QPixmap>

#include "gameitem.h"

#define PIG_DENSITY 50.0f
#define PIG_FRICTION 10.0f
#define PIG_RESTITUTION 0.50f

class Pig : public GameItem
{
    public:
        Pig(float x, float y, float r, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);

        b2BodyDef bodydef;
};
#endif // PIG_H



