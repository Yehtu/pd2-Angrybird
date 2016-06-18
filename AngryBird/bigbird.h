#ifndef BIGBIRD_H
#define BIGBIRD_H

#include "bird.h"

class Bigbird : public Bird
{
public:
    Bigbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual void skill();
};

#endif // BIGBIRD_H
