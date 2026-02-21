#ifndef EEZ_LVGL_UI_VARS_H
#define EEZ_LVGL_UI_VARS_H

#include <stdint.h>
#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// enum declarations



// Flow global variables

enum FlowGlobalVariables {
    FLOW_GLOBAL_VARIABLE_LUZ_COMEDOR_STATE = 0,
    FLOW_GLOBAL_VARIABLE_LUZ_LIVING_STATE = 1,
    FLOW_GLOBAL_VARIABLE_LUZ_DORMITORIO_C_STATE = 2,
    FLOW_GLOBAL_VARIABLE_LUZ_DORMITORIO_G_STATE = 3,
    FLOW_GLOBAL_VARIABLE_LUZ_OFICINA_T_STATE = 4,
    FLOW_GLOBAL_VARIABLE_LUZ_OFICINA_L_STATE = 5,
    FLOW_GLOBAL_VARIABLE_TEMP = 6,
    FLOW_GLOBAL_VARIABLE_DATE = 7,
    FLOW_GLOBAL_VARIABLE_BRIGHTNESS = 8,
    FLOW_GLOBAL_VARIABLE_CONFIG_SCREEN = 9
};

// Native global variables

extern bool get_var_luz_comedor_state();
extern void set_var_luz_comedor_state(bool value);
extern bool get_var_luz_living_state();
extern void set_var_luz_living_state(bool value);
extern bool get_var_luz_dormitorio_c_state();
extern void set_var_luz_dormitorio_c_state(bool value);
extern bool get_var_luz_dormitorio_g_state();
extern void set_var_luz_dormitorio_g_state(bool value);
extern bool get_var_luz_oficina_t_state();
extern void set_var_luz_oficina_t_state(bool value);
extern bool get_var_luz_oficina_l_state();
extern void set_var_luz_oficina_l_state(bool value);
extern const char *get_var_temp();
extern void set_var_temp(const char *value);
extern const char *get_var_date();
extern void set_var_date(const char *value);
extern int32_t get_var_brightness();
extern void set_var_brightness(int32_t value);
extern const char *get_var_config_screen();
extern void set_var_config_screen(const char *value);


#ifdef __cplusplus
}
#endif

#endif /*EEZ_LVGL_UI_VARS_H*/