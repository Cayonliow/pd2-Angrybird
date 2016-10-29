#include "bigbird.h"

Bigbird::Bigbird(float x, float y, float r, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene) :Bird(x, y, r, timer, pixmap, world, scene)
{

}

void Bigbird::set_linear_velocity(b2Vec2 velocity)
{
    g_body->SetLinearVelocity(velocity);
}


void Bigbird::SpecialSkill()
{
    g_body->SetAngularVelocity(20);
}
