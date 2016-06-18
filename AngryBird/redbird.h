#ifndef REDBIRD_H
#define REDBIRD_H

#include "bird.h"

class Redbird : public Bird
{
public:
    Redbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual void skill();
};

#endif // REDBIRD_H
