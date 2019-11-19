//
// Created by skidr on 14/11/2019.
//

#ifndef LAB5_VIDEO_GR_H
#define LAB5_VIDEO_GR_H

#include <lcom/lcf.h>
#include "sprite.h"

int vg_draw_pattern(uint8_t no_rectangles, uint32_t first, uint8_t step);
int vg_draw_pixmap(xpm_map_t xpm, uint16_t x, uint16_t y);
int vg_draw_sprite(Sprite *sprite);
int vg_erase_sprite(Sprite *sprite);
int vg_vbe_controller_info(struct vg_vbe_contr_info *vci_p);


#endif //LAB5_VIDEO_GR_H

