//
// Created by skidr on 16/11/2019.
//

#include "sprite.h"

Sprite *create_sprite(xpm_map_t xpm, int x, int y, int xspeed, int yspeed) {
    //allocate space for the "object"
    xpm_image_t img;
    Sprite *sp = (Sprite *) malloc ( sizeof(Sprite));
    if( sp == NULL )
        return NULL;
    // read the sprite pixmap
    sp->map = (char*) xpm_load(xpm, XPM_INDEXED, &img);
    if( sp->map == NULL ) {
        free(sp);
        return NULL;
    }

    sp->height = img.height;
    sp->width = img.width;
    sp->x = x;
    sp->y = y;
    sp->xspeed = xspeed;
    sp->yspeed = yspeed;

    return sp;
}
