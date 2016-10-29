#ifndef BLOCK_H
#define BLOCK_H

#include <QGraphicsScene>
#include <QPixmap>
#include <QTimer>

#include "gameitem.h"

#define BLOCK_DENSITY 20.0f
#define BLOCK_FRICTION 1.0f
#define BLOCK_RESTITUTION 0.50f

class Block:public GameItem
{
    public:
    Block(float x, float y, float width, float height, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};


#endif // BLOCK_H
