#include "bird.h"

Bird::Bird(float x, float y, float r, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene) : GameItem(world)
{
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    g_size = QSize(r*2,r*2);

    radius=r;
    bodyshape.m_radius = r;

    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;
    bodydef.position.Set(x,y);
    bodydef.userData = this;
    g_body = world->CreateBody(&bodydef);

    fixturedef.shape = &bodyshape;
    fixturedef.density = BIRD_DENSITY;
    fixturedef.friction = BIRD_FRICTION;
    fixturedef.restitution = BIRD_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);

    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
}

void Bird::set_linear_velocity(b2Vec2 velocity)
{
    g_body->SetLinearVelocity(velocity);
}

void Bird::set_type_of_body(bool check)
{
    if(check==true)bodydef.type = b2_dynamicBody;
    if(check==false)bodydef.type = b2_staticBody;
}

void Bird::SpecialSkill()
{

}

