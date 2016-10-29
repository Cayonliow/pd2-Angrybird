#ifndef SLING_H
#define SLING_H


#include <QGraphicsScene>
#include <QPixmap>

#include "gameitem.h"


class Sling:public GameItem
{
    public:
        Sling(float x,float y,float w,float h,QPixmap pixmap,b2World *world,QGraphicsScene *scene);

        b2PolygonShape bodyBox;
};


#endif // SLING_H
