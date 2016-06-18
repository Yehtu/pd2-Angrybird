#ifndef ROCK_H
#define ROCK_H

#include "gameitem.h"
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define ROCK_DENSITY 8.0f
#define ROCK_FRICTION 0.7f
#define ROCK_RESTITUTION 0.4f

class Rock : public GameItem
{
public:
    Rock(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    Rock(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    b2Vec2 getLinearVelocity();
};

#endif // ROCK_H
