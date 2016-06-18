#ifndef WHITEBIRD_H
#define WHITEBIRD_H

#include "bird.h"
//#include "egg.h"

class Whitebird : public Bird
{
public:
    Whitebird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
    virtual void skill();
    /*Egg *egg;
    QGraphicsScene *scene;
    b2World *world;
    QList<GameItem *> itemList;
    QTimer timer;*/
};

#endif // WHITEBIRD_H
