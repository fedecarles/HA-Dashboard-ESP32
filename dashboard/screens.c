#include <string.h>

#include "screens.h"
#include "images.h"
#include "fonts.h"
#include "actions.h"
#include "vars.h"
#include "styles.h"
#include "ui.h"

#include <string.h>

objects_t objects;
lv_obj_t *tick_value_change_obj;
uint32_t active_theme_index = 0;

static void event_handler_cb_main_obj0(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            set_var_luz_comedor_state(value);
        }
    }
}

static void event_handler_cb_main_obj1(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            set_var_luz_living_state(value);
        }
    }
}

static void event_handler_cb_main_obj2(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            set_var_luz_dormitorio_g_state(value);
        }
    }
}

static void event_handler_cb_main_obj3(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            set_var_luz_dormitorio_c_state(value);
        }
    }
}

static void event_handler_cb_main_obj4(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            set_var_luz_oficina_t_state(value);
        }
    }
}

static void event_handler_cb_main_obj5(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            bool value = lv_obj_has_state(ta, LV_STATE_CHECKED);
            set_var_luz_oficina_l_state(value);
        }
    }
}

static void event_handler_cb_config_brightness(lv_event_t *e) {
    lv_event_code_t event = lv_event_get_code(e);
    if (event == LV_EVENT_VALUE_CHANGED) {
        lv_obj_t *ta = lv_event_get_target(e);
        if (tick_value_change_obj != ta) {
            int32_t value = lv_slider_get_value(ta);
            set_var_brightness(value);
        }
    }
}

void create_screen_main() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.main = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_set_style_bg_img_src(obj, &img_background, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // temp
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.temp = obj;
            lv_obj_set_pos(obj, 539, 292);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
        {
            lv_obj_t *obj = lv_switch_create(parent_obj);
            objects.obj0 = obj;
            lv_obj_set_pos(obj, 174, 59);
            lv_obj_set_size(obj, 175, 69);
            lv_obj_add_event_cb(obj, action_toggle_luz_comedor, LV_EVENT_CLICKED, (void *)0);
            lv_obj_add_event_cb(obj, event_handler_cb_main_obj0, LV_EVENT_ALL, 0);
        }
        {
            lv_obj_t *obj = lv_switch_create(parent_obj);
            objects.obj1 = obj;
            lv_obj_set_pos(obj, 174, 160);
            lv_obj_set_size(obj, 175, 69);
            lv_obj_add_event_cb(obj, action_toggle_luz_living, LV_EVENT_PRESSED, (void *)0);
            lv_obj_add_event_cb(obj, event_handler_cb_main_obj1, LV_EVENT_ALL, 0);
        }
        {
            lv_obj_t *obj = lv_switch_create(parent_obj);
            objects.obj2 = obj;
            lv_obj_set_pos(obj, 174, 257);
            lv_obj_set_size(obj, 175, 69);
            lv_obj_add_event_cb(obj, action_toggle_luz_dormitorio_g, LV_EVENT_PRESSED, (void *)0);
            lv_obj_add_event_cb(obj, event_handler_cb_main_obj2, LV_EVENT_ALL, 0);
        }
        {
            lv_obj_t *obj = lv_switch_create(parent_obj);
            objects.obj3 = obj;
            lv_obj_set_pos(obj, 174, 351);
            lv_obj_set_size(obj, 175, 69);
            lv_obj_add_event_cb(obj, action_toggle_luz_dormitorio_c, LV_EVENT_PRESSED, (void *)0);
            lv_obj_add_event_cb(obj, event_handler_cb_main_obj3, LV_EVENT_ALL, 0);
        }
        {
            lv_obj_t *obj = lv_switch_create(parent_obj);
            objects.obj4 = obj;
            lv_obj_set_pos(obj, 546, 59);
            lv_obj_set_size(obj, 175, 69);
            lv_obj_add_event_cb(obj, action_toggle_luz_oficina_t, LV_EVENT_PRESSED, (void *)0);
            lv_obj_add_event_cb(obj, event_handler_cb_main_obj4, LV_EVENT_ALL, 0);
        }
        {
            lv_obj_t *obj = lv_switch_create(parent_obj);
            objects.obj5 = obj;
            lv_obj_set_pos(obj, 546, 160);
            lv_obj_set_size(obj, 175, 69);
            lv_obj_add_event_cb(obj, action_toggle_luz_oficina_l, LV_EVENT_PRESSED, (void *)0);
            lv_obj_add_event_cb(obj, event_handler_cb_main_obj5, LV_EVENT_ALL, 0);
        }
        {
            // comedor_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.comedor_label = obj;
            lv_obj_set_pos(obj, 21, 80);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Comedor");
        }
        {
            // living_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.living_label = obj;
            lv_obj_set_pos(obj, 21, 181);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Living");
        }
        {
            // dormitorio_g_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.dormitorio_g_label = obj;
            lv_obj_set_pos(obj, 16, 278);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Dormitorio G");
        }
        {
            // dormitorio_c_label
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.dormitorio_c_label = obj;
            lv_obj_set_pos(obj, 16, 373);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Dormitorio C");
        }
        {
            // oficina_t
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.oficina_t = obj;
            lv_obj_set_pos(obj, 429, 80);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Oficina T");
        }
        {
            // oficina_l
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.oficina_l = obj;
            lv_obj_set_pos(obj, 431, 181);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "Oficina L");
        }
        {
            // dormc
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.dormc = obj;
            lv_obj_set_pos(obj, 350, 351);
            lv_obj_set_size(obj, 81, 69);
            lv_obj_add_event_cb(obj, action_config_dormc, LV_EVENT_CLICKED, (void *)0);
            lv_obj_set_style_bg_img_src(obj, &img_gear, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_opa(obj, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2196f3), LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // dormg
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.dormg = obj;
            lv_obj_set_pos(obj, 350, 257);
            lv_obj_set_size(obj, 81, 69);
            lv_obj_add_event_cb(obj, action_config_dormg, LV_EVENT_CLICKED, (void *)0);
            lv_obj_set_style_bg_img_src(obj, &img_gear, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2196f3), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // living_lampara
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.living_lampara = obj;
            lv_obj_set_pos(obj, 350, 160);
            lv_obj_set_size(obj, 81, 69);
            lv_obj_add_event_cb(obj, action_config_living, LV_EVENT_CLICKED, (void *)0);
            lv_obj_set_style_bg_img_src(obj, &img_gear, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2196f3), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // comedor_mesa
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.comedor_mesa = obj;
            lv_obj_set_pos(obj, 348, 59);
            lv_obj_set_size(obj, 81, 69);
            lv_obj_add_event_cb(obj, action_config_comedor, LV_EVENT_PRESSED, (void *)0);
            lv_obj_set_style_bg_img_src(obj, &img_gear, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2196f3), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // office
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.office = obj;
            lv_obj_set_pos(obj, 719, 59);
            lv_obj_set_size(obj, 81, 69);
            lv_obj_add_event_cb(obj, action_config_office, LV_EVENT_CLICKED, (void *)0);
            lv_obj_set_style_bg_img_src(obj, &img_gear, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2196f3), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // office_pie
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.office_pie = obj;
            lv_obj_set_pos(obj, 719, 160);
            lv_obj_set_size(obj, 81, 69);
            lv_obj_add_event_cb(obj, action_config_office_pie, LV_EVENT_CLICKED, (void *)0);
            lv_obj_set_style_bg_img_src(obj, &img_gear, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff2196f3), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_opa(obj, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
        }
        {
            // date
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.date = obj;
            lv_obj_set_pos(obj, 539, 359);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_38, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
    }
    
    tick_screen_main();
}

void tick_screen_main() {
    {
        const char *new_val = get_var_temp();
        const char *cur_val = lv_label_get_text(objects.temp);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.temp;
            lv_label_set_text(objects.temp, new_val);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_luz_comedor_state();
        bool cur_val = lv_obj_has_state(objects.obj0, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj0;
            if (new_val) lv_obj_add_state(objects.obj0, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj0, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_luz_living_state();
        bool cur_val = lv_obj_has_state(objects.obj1, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj1;
            if (new_val) lv_obj_add_state(objects.obj1, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj1, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_luz_dormitorio_g_state();
        bool cur_val = lv_obj_has_state(objects.obj2, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj2;
            if (new_val) lv_obj_add_state(objects.obj2, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj2, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_luz_dormitorio_c_state();
        bool cur_val = lv_obj_has_state(objects.obj3, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj3;
            if (new_val) lv_obj_add_state(objects.obj3, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj3, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_luz_oficina_t_state();
        bool cur_val = lv_obj_has_state(objects.obj4, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj4;
            if (new_val) lv_obj_add_state(objects.obj4, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj4, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        bool new_val = get_var_luz_oficina_l_state();
        bool cur_val = lv_obj_has_state(objects.obj5, LV_STATE_CHECKED);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.obj5;
            if (new_val) lv_obj_add_state(objects.obj5, LV_STATE_CHECKED);
            else lv_obj_clear_state(objects.obj5, LV_STATE_CHECKED);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_date();
        const char *cur_val = lv_label_get_text(objects.date);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.date;
            lv_label_set_text(objects.date, new_val);
            tick_value_change_obj = NULL;
        }
    }
}

void create_screen_config() {
    lv_obj_t *obj = lv_obj_create(0);
    objects.config = obj;
    lv_obj_set_pos(obj, 0, 0);
    lv_obj_set_size(obj, 800, 480);
    lv_obj_set_style_bg_img_src(obj, &img_background, LV_PART_MAIN | LV_STATE_DEFAULT);
    {
        lv_obj_t *parent_obj = obj;
        {
            // brightness
            lv_obj_t *obj = lv_slider_create(parent_obj);
            objects.brightness = obj;
            lv_obj_set_pos(obj, 106, 38);
            lv_obj_set_size(obj, 55, 415);
            lv_obj_add_event_cb(obj, action_change_brightness, LV_EVENT_RELEASED, (void *)0);
            lv_obj_add_event_cb(obj, event_handler_cb_config_brightness, LV_EVENT_ALL, 0);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xff000000), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_grad_color(obj, lv_color_hex(0xff605656), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_text_color(obj, lv_color_hex(0xffffffff), LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_obj_set_style_bg_color(obj, lv_color_hex(0xfff5f5f5), LV_PART_KNOB | LV_STATE_DEFAULT);
        }
        {
            // go_back_btn
            lv_obj_t *obj = lv_btn_create(parent_obj);
            objects.go_back_btn = obj;
            lv_obj_set_pos(obj, 618, 391);
            lv_obj_set_size(obj, 138, 62);
            lv_obj_add_event_cb(obj, action_go_to_main, LV_EVENT_CLICKED, (void *)0);
            {
                lv_obj_t *parent_obj = obj;
                {
                    lv_obj_t *obj = lv_label_create(parent_obj);
                    lv_obj_set_pos(obj, 0, 0);
                    lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
                    lv_obj_set_style_align(obj, LV_ALIGN_CENTER, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_obj_set_style_text_font(obj, &lv_font_montserrat_24, LV_PART_MAIN | LV_STATE_DEFAULT);
                    lv_label_set_text(obj, "Back");
                }
            }
        }
        {
            // config_title
            lv_obj_t *obj = lv_label_create(parent_obj);
            objects.config_title = obj;
            lv_obj_set_pos(obj, 353, 38);
            lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
            lv_obj_set_style_text_font(obj, &lv_font_montserrat_48, LV_PART_MAIN | LV_STATE_DEFAULT);
            lv_label_set_text(obj, "");
        }
    }
    
    tick_screen_config();
}

void tick_screen_config() {
    {
        int32_t new_val = get_var_brightness();
        int32_t cur_val = lv_slider_get_value(objects.brightness);
        if (new_val != cur_val) {
            tick_value_change_obj = objects.brightness;
            lv_slider_set_value(objects.brightness, new_val, LV_ANIM_OFF);
            tick_value_change_obj = NULL;
        }
    }
    {
        const char *new_val = get_var_config_screen();
        const char *cur_val = lv_label_get_text(objects.config_title);
        if (strcmp(new_val, cur_val) != 0) {
            tick_value_change_obj = objects.config_title;
            lv_label_set_text(objects.config_title, new_val);
            tick_value_change_obj = NULL;
        }
    }
}



typedef void (*tick_screen_func_t)();
tick_screen_func_t tick_screen_funcs[] = {
    tick_screen_main,
    tick_screen_config,
};
void tick_screen(int screen_index) {
    tick_screen_funcs[screen_index]();
}
void tick_screen_by_id(enum ScreensEnum screenId) {
    tick_screen_funcs[screenId - 1]();
}

void create_screens() {
    lv_disp_t *dispp = lv_disp_get_default();
    lv_theme_t *theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED), true, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);
    
    create_screen_main();
    create_screen_config();
}
