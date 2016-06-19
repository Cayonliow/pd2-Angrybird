#include "sling.h"

Sling::Sling(float x,float y,float w,float h,QPixmap pixmap,b2World *world,QGraphicsScene *scene):GameItem(world)
{
   // g_size=QSize(-60,20);
    g_pixmap.setPixmap(pixmap);
    g_size = QSize(w-2.7,h+1.0);
    //g_size = QSize(w,h/2);

    b2BodyDef bodyDef;
    bodyDef.type = b2_staticBody;
    bodyDef.userData = this;
    bodyDef.position.Set(x,y);
    g_body = world->CreateBody(&bodyDef);


    b2PolygonShape bodyBox;
    bodyBox.SetAsBox(w/2,h/2);

    g_body->CreateFixture(&bodyBox,9.0f);

    scene->addItem(&g_pixmap);
    paint();
}
