#ifndef EEZ_LVGL_UI_SCREENS_H
#define EEZ_LVGL_UI_SCREENS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct _objects_t {
    lv_obj_t *main;
    lv_obj_t *config;
    lv_obj_t *obj0;
    lv_obj_t *obj1;
    lv_obj_t *obj2;
    lv_obj_t *obj3;
    lv_obj_t *obj4;
    lv_obj_t *obj5;
    lv_obj_t *temp;
    lv_obj_t *comedor_label;
    lv_obj_t *living_label;
    lv_obj_t *dormitorio_g_label;
    lv_obj_t *dormitorio_c_label;
    lv_obj_t *oficina_t;
    lv_obj_t *oficina_l;
    lv_obj_t *dormc;
    lv_obj_t *dormg;
    lv_obj_t *living_lampara;
    lv_obj_t *comedor_mesa;
    lv_obj_t *office;
    lv_obj_t *office_pie;
    lv_obj_t *date;
    lv_obj_t *brightness;
    lv_obj_t *go_back_btn;
    lv_obj_t *config_title;
} objects_t;

extern objects_t objects;

enum ScreensEnum {
    SCREEN_ID_MAIN = 1,
    SCREEN_ID_CONFIG = 2,
};

void create_screen_main();
void tick_screen_main();

void create_screen_config();
void tick_screen_config();

void tick_screen_by_id(enum ScreensEnum screenId);
void tick_screen(int screen_index);

void create_screens();


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_SCREENS_H*/