#include "bluebird.h"

Bluebird::Bluebird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene):Bird(x, y, radius, timer, pixmap, world, scene)
{

}

void Bluebird::skill()
{
    /*float bx, by;
    bx = getPosition().x;
    by = getPosition().y;
    int vx, vy;
    vx = getLinearVelocity().x;
    vy = getLinearVelocity().y;
    b1 = new Bluebirds(bx, by+5, 0.4f, &timer, QPixmap(":/image/BlueBird.png"), world, scene);
    b1->setLinearVelocity(b2Vec2(vx, vy+2));
    itemList.push_back(b1);    
    b2 = new Bluebirds(bx, by-5, 0.4f, &timer, QPixmap(":/image/BlueBird.png"), world, scene);
    b2->setLinearVelocity(b2Vec2(vx, vy-2));
    itemList.push_back(b2);*/
}
