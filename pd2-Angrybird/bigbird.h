#ifndef BIGBIRD_H
#define BIGBIRD_H

#include <QGraphicsScene>
#include <QTimer>
#include <QPixmap>

#include "gameitem.h"
#include "bird.h"

#define BIRD_DENSITY 50.0f
#define BIRD_FRICTION 10.0f
#define BIRD_RESTITUTION 0.50f

class Bigbird : public Bird
{
    public:
        Bigbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
        void set_linear_velocity(b2Vec2 velocity);

        virtual void SpecialSkill();

        b2BodyDef bodydef;
        b2CircleShape bodyshape;
        b2FixtureDef fixturedef;
        int radius;
};

#endif // BIGBIRD_H




