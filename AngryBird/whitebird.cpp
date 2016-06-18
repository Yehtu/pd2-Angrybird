#include "whitebird.h"

Whitebird::Whitebird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):Bird(x, y, radius, timer, pixmap, world, scene)
{

}

void Whitebird::skill()
{
    setLinearVelocity(b2Vec2(getLinearVelocity().x,getLinearVelocity().y+8));
    //egg = new Egg(getPosition().x, getPosition().y-2, 0.4f, &timer, QPixmap(":/image/egg.png"), world, scene);
    //itemList.push_back(egg);
}
