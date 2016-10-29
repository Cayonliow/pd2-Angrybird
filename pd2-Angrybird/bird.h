#ifndef BIRD_H
#define BIRD_H

#include <QGraphicsScene>
#include <QTimer>
#include <QPixmap>

#include "gameitem.h"

#define BIRD_DENSITY 50.0f
#define BIRD_FRICTION 10.0f
#define BIRD_RESTITUTION 0.50f

class Bird : public GameItem
{
    public:
        Bird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);

        void set_linear_velocity(b2Vec2 velocity);
        void set_type_of_body(bool check);

        virtual void SpecialSkill();

        b2BodyDef bodydef;
        b2FixtureDef fixturedef;
        b2CircleShape bodyshape;

        int radius;
};

#endif // BIRD_H
