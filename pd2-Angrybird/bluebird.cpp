#include "bluebird.h"

Bluebird::Bluebird(float x, float y, float r, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene) : Bird(x, y, r, timer, pixmap, world, scene)
{
    radius=r;
}

void Bluebird::SpecialSkill()
{
     g_body->SetLinearVelocity(b2Vec2(0,-20));
}
