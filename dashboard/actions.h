#ifndef EEZ_LVGL_UI_EVENTS_H
#define EEZ_LVGL_UI_EVENTS_H

#include <lvgl.h>

#ifdef __cplusplus
extern "C" {
#endif

extern void action_toggle_luz_comedor(lv_event_t * e);
extern void action_toggle_luz_living(lv_event_t * e);
extern void action_toggle_luz_dormitorio_c(lv_event_t * e);
extern void action_toggle_luz_dormitorio_g(lv_event_t * e);
extern void action_toggle_luz_oficina_t(lv_event_t * e);
extern void action_toggle_luz_oficina_l(lv_event_t * e);
extern void action_go_to_main(lv_event_t * e);
extern void action_change_brightness(lv_event_t * e);
extern void action_config_comedor(lv_event_t * e);
extern void action_config_living(lv_event_t * e);
extern void action_config_dormg(lv_event_t * e);
extern void action_config_dormc(lv_event_t * e);
extern void action_config_office(lv_event_t * e);
extern void action_config_office_pie(lv_event_t * e);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_EVENTS_H*/