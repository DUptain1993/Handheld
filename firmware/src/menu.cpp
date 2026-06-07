#include "menu.h"
#include "ui.h"
#include "display.h"
#include "touch.h"
#include "wifi.h"
#include "http.h"
#include "../include/config.h"

static MenuState current_state = STATE_MAIN_MENU;
static bool needs_redraw = true;
static String output_buffer = "";
static const char* current_title = "CYBERDECK";

struct MenuItem {
    const char* label;
    const char* cmd;
    MenuState next;
};

// Hierarchy matching ESP32-TOOLS-PRO-480x320
static MenuItem main_menu[] = {
    {"WIFI TOOLS", "", STATE_WIFI_TOOLS},
    {"RADIO TOOLS", "", STATE_RADIO_TOOLS},
    {"BLUETOOTH", "", STATE_BLUETOOTH},
    {"MONITOR", "", STATE_MONITOR},
    {"SYSTEM", "", STATE_SYSTEM}
};

static MenuItem wifi_tools[] = {
    {"WiFi Scanner", "run=wifi_scan", STATE_CMD_OUTPUT},
    {"Beacon Spam", "run=beacon_spam", STATE_CMD_OUTPUT},
    {"Deauther", "run=deauther", STATE_CMD_OUTPUT},
    {"Evil Portal", "run=evil_portal", STATE_CMD_OUTPUT},
    {"Probe Sniffer", "run=probe_sniffer", STATE_CMD_OUTPUT},
    {"KARMA Attack", "run=karma", STATE_CMD_OUTPUT},
    {"< BACK", "", STATE_MAIN_MENU}
};

static MenuItem radio_tools[] = {
    {"Jammer", "run=radio_jammer", STATE_CMD_OUTPUT},
    {"Spectrum", "run=radio_scanner", STATE_CMD_OUTPUT},
    {"< BACK", "", STATE_MAIN_MENU}
};

static MenuItem system_menu[] = {
    {"Settings", "run=settings", STATE_CMD_OUTPUT},
    {"System Info", "run=sysinfo", STATE_CMD_OUTPUT},
    {"Clock & Weather", "run=clock", STATE_CMD_OUTPUT},
    {"About", "run=about", STATE_CMD_OUTPUT},
    {"< BACK", "", STATE_MAIN_MENU}
};

void menu_init() {
    output_buffer.reserve(MAX_RESPONSE_SIZE + 100);
    menu_set_state(STATE_MAIN_MENU);
}

void menu_set_state(MenuState state) {
    current_state = state;
    needs_redraw = true;
    display_clear();
}

void draw_list(const char* title, MenuItem* items, int count) {
    ui_draw_header(title);
    for (int i = 0; i < count; i++) {
        ui_draw_list_item(10, 50 + (i * 40), 460, 38, items[i].label, false);
    }
}

void draw_output() {
    ui_draw_header("COMMAND OUTPUT");
    ui_draw_output_box(10, 50, 460, 200, output_buffer);
    ui_draw_button(10, 260, 100, 50, "BACK", false);
}

bool hit_test(uint16_t tx, uint16_t ty, int x, int y, int w, int h) {
    return (tx >= x && tx <= x + w && ty >= y && ty <= y + h);
}

void handle_list_click(MenuItem* items, int count, uint16_t tx, uint16_t ty) {
    for (int i = 0; i < count; i++) {
        if (hit_test(tx, ty, 10, 50 + (i * 40), 460, 38)) {
            if (items[i].next == STATE_CMD_OUTPUT) {
                display_clear();
                ui_draw_header("EXECUTING...");
                display_print("Waiting for Pi backend...", 20, 100, 2, UI_TEXT_COLOR);
                http_send_command("/cmd", items[i].cmd, output_buffer);
                menu_set_state(STATE_CMD_OUTPUT);
            } else {
                menu_set_state(items[i].next);
            }
            return;
        }
    }
}

void menu_update() {
    if (needs_redraw) {
        switch (current_state) {
            case STATE_MAIN_MENU:  draw_list("CYBERDECK", main_menu, 5); break;
            case STATE_WIFI_TOOLS: draw_list("WIFI TOOLS", wifi_tools, 7); break;
            case STATE_RADIO_TOOLS: draw_list("RADIO TOOLS", radio_tools, 3); break;
            case STATE_SYSTEM:     draw_list("SYSTEM", system_menu, 5); break;
            case STATE_CMD_OUTPUT: draw_output(); break;
            default:
                ui_draw_header("UNDER DEVELOPMENT");
                ui_draw_button(10, 260, 100, 50, "BACK", false);
                break;
        }
        needs_redraw = false;
    }

    uint16_t tx, ty;
    if (touch_read(&tx, &ty)) {
        switch (current_state) {
            case STATE_MAIN_MENU:  handle_list_click(main_menu, 5, tx, ty); break;
            case STATE_WIFI_TOOLS: handle_list_click(wifi_tools, 7, tx, ty); break;
            case STATE_RADIO_TOOLS: handle_list_click(radio_tools, 3, tx, ty); break;
            case STATE_SYSTEM:     handle_list_click(system_menu, 5, tx, ty); break;
            case STATE_CMD_OUTPUT:
                if (hit_test(tx, ty, 10, 260, 100, 50)) menu_set_state(STATE_MAIN_MENU);
                break;
            default:
                if (hit_test(tx, ty, 10, 260, 100, 50)) menu_set_state(STATE_MAIN_MENU);
                break;
        }
    }
}
