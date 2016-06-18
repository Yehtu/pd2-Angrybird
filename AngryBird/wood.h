#ifndef WOOD_H
#define WOOD_H

#include "gameitem.h"
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define WOOD_DENSITY 5.0f
#define WOOD_FRICTION 0.6f
#define WOOD_RESTITUTION 0.4f

class Wood : public GameItem
{
public:
    Wood(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    b2Vec2 getLinearVelocity();
};

#endif // WOOD_H
