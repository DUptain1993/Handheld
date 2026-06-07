#ifndef MENU_H
#define MENU_H

enum MenuState {
    STATE_MAIN_MENU,
    STATE_WIFI_TOOLS,
    STATE_RADIO_TOOLS,
    STATE_BLUETOOTH,
    STATE_MONITOR,
    STATE_SYSTEM,
    STATE_CMD_OUTPUT
};

void menu_init();
void menu_update();
void menu_set_state(MenuState state);

#endif
