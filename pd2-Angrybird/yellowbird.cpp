#include "yellowbird.h"

Yellowbird::Yellowbird(float x, float y, float r, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene) : Bird(x, y, r, timer, pixmap, world, scene)
{

}

void Yellowbird::SpecialSkill()
{
    g_body->SetLinearVelocity(b2Vec2(20,0));
}

