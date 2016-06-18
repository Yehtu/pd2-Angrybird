#ifndef BLUEBIRD_H
#define BLUEBIRD_H

#include "bird.h"

class Bluebird : public Bird
{
public:
    Bluebird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);    
    virtual void skill();
    /*Bluebirds *b1;
    Bluebirds *b2;*/

};

#endif // BLUEBIRD_H
