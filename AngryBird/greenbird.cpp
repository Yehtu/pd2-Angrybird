#include "greenbird.h"

Greenbird::Greenbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):Bird(x, y, radius, timer, pixmap, world, scene)
{

}

void Greenbird::skill()
{
    setLinearVelocity(b2Vec2(-(getLinearVelocity().x+3),-1));
}
