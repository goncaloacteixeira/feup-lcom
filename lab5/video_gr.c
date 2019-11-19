//
// Created by skidr on 14/11/2019.
//

#include <lcom/lcf.h>
#include <machine/int86.h>
#include <lcom/video_gr.h>
#include <lcom/lab5.h>
#include <lcom/liblm.h>
#include <lcom/vbe.h>

#include "video_gr.h"
#include "timer.h"

static unsigned x_res;
static unsigned y_res;
static unsigned bits_per_pixel;
static unsigned int vram_base;
static unsigned int vram_size;
static uint8_t memory_model;
static uint8_t red_mask_size;
static uint8_t green_mask_size;
static uint8_t blue_mask_size;
static char *video_mem;


void *(vg_init)(uint16_t mode) {
    struct reg86 r86;

    memset(&r86, 0, sizeof(r86));

    r86.intno = 0x10;
    r86.ax = 0x4f02;
    r86.bx = 1 << 14 | mode;

    vbe_mode_info_t vbe;

    vbe_get_mode_info(mode, &vbe);

    x_res = vbe.XResolution;
    y_res = vbe.YResolution;
    bits_per_pixel = vbe.BitsPerPixel;
    memory_model = vbe.MemoryModel;
    red_mask_size = vbe.RedMaskSize;
    green_mask_size = vbe.GreenMaskSize;
    blue_mask_size = vbe.BlueMaskSize;

    struct minix_mem_range mr;
    vram_base = (unsigned int)vbe.PhysBasePtr;
    vram_size = x_res * y_res * (bits_per_pixel / 8);

    mr.mr_base = vram_base;
    mr.mr_limit = mr.mr_base + vram_size;

    int r;

    if (OK != (r = sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)))
        panic("sys_privctl (ADD_MEM) failed: %d\n", r);

    /* Map memory */

    video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);

    if (video_mem == MAP_FAILED)
        panic("couldn't map video memory");

    if (sys_int86(&r86) != OK)
    {
        printf("set_vbe_mode: sys_int86() failed \n");
        return NULL;
    }

    return video_mem;
}


int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
    if (x < 0 || y < 0 || x > x_res || y > y_res || x + width > x_res || y + height > y_res) {
        printf("overflow\n");
        return -1;
    }

    for (int i = 0; i < height; i++) {
        vg_draw_hline(x, y + i, width, color);
    }

    return 0;
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {

    if (x < 0 || y < 0 || x > x_res || y > y_res || x + len > x_res) {
        printf("overflow\n");
        return -1;
    }

    for (int i = 0; i < len; i++)
        memcpy(video_mem + x_res * y * (bits_per_pixel / 8) + (x + i) * bits_per_pixel / 8, &color, bits_per_pixel / 8);

    return 0;
}

int vg_draw_pattern(uint8_t no_rectangles, uint32_t first, uint8_t step) {

    uint32_t width = x_res / no_rectangles;
    uint32_t height = y_res / no_rectangles;

    uint8_t r_first = first >> bits_per_pixel / 3 * 2;
    uint8_t g_first = first >> bits_per_pixel / 3 & 0x00FF;
    uint8_t b_first = first & 0x00FF;

    for (int row = 0; row < no_rectangles; row++)
    {
        for (int col = 0; col < no_rectangles; col++)
        {
            if (memory_model == 0x04) {
                uint8_t index = (first + (row * no_rectangles + col) * step) % (1 << bits_per_pixel);
                vg_draw_rectangle(0 + (col * width), (row * height), width, height, index);
            }
            else if (memory_model == 0x06 || memory_model == 0x07) {
                uint8_t R = (r_first + col * step) % (1 << red_mask_size);
                uint8_t G = (g_first + row * step) % (1 << green_mask_size);
                uint8_t B = (b_first + (col + row) * step) % (1 << blue_mask_size);
                uint32_t color = ((uint32_t) R << bits_per_pixel / 3 * 2) | ((uint32_t) G << bits_per_pixel / 3) | (uint32_t) B;
                vg_draw_rectangle(0 + (col * width), (row * height), width, height, color);
            }
        }
    }
    return 0;
}

void change_color(uint16_t x, uint16_t y, uint32_t color) {
    memcpy(video_mem + x_res * y * (bits_per_pixel / 8) + x * bits_per_pixel / 8, &color, bits_per_pixel / 8);
    return;
}

int vg_draw_pixmap(xpm_map_t xpm, uint16_t x, uint16_t y) {
    xpm_image_t img;
    uint8_t *map;
    // get the pixmap from the XPM
    map = xpm_load(xpm, XPM_INDEXED, &img);
    // copy it to graphics memory

    for (int i = 0; i < img.height; i++) {
        for (int j = 0; j < img.width; j++) {
            uint32_t color = map[j + i*img.width];
            change_color(x+j, y+i, color);
        }
    }

    return 0;
}

int vg_draw_sprite(Sprite *sprite) {
    int x = sprite->width;
    int y = sprite->height;

    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            uint32_t color = sprite->map[j + i*x];
            change_color(sprite->x + j, sprite->y + i, color);
        }
    }

    return 0;
}

int vg_erase_sprite(Sprite *sprite) {
    int y = sprite->height;
    int x = sprite->width;

    for (int i = 0; i < y; i++) {
        for (int j = 0; j < x; j++) {
            change_color(sprite->x + j, sprite->y + i, TRANSPARENCY_COLOR_1_5_5_5);
        }
    }
    return 0;
}

int vg_vbe_controller_info(struct vg_vbe_contr_info *vbeContrInfo) {
    mmap_t temp;
    if (lm_alloc(sizeof(struct vg_vbe_contr_info), &temp) == NULL)
        return 1;

    struct reg86 r86;
    memset(&r86, 0, sizeof(r86));
    r86.intno = 0x10;
    r86.ax = 0x4F00;
    r86.es = PB2BASE(temp.phys);
    r86.di = PB2OFF(temp.phys);

    if (sys_int86(&r86) != 0) {
        printf("error::sys_int86(&r86)\n");
        return 1;
    }

    memcpy(vbeContrInfo, temp.virt, temp.size);
    lm_free(&temp);
    return 0;
}





