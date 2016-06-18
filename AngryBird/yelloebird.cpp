#include "yellowbird.h"

Yellowbird::Yellowbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):Bird(x, y, radius, timer, pixmap, world, scene)
{

}

void Yellowbird::skill()
{
    setLinearVelocity(b2Vec2(getLinearVelocity().x+30,getLinearVelocity().y-1));
}
