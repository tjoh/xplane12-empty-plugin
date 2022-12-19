#include "XPLMMenus.h"
#include <string.h>

#ifndef XPLM400
#error This is made to be compiled against the XPLM400 SDK
#endif

int g_menu_container_idx; // The index of our menu item in the Plugins menu
XPLMMenuID g_menu_id; // The menu container we'll append all our menu items to
void menu_handler(void *, void *);

PLUGIN_API int XPluginStart(char *outName, char *outSig, char *outDesc) {
  strcpy(outName, PLUGIN_NAME);
  strcpy(outSig, "xpsdk.examples.emptyplugin");
  strcpy(outDesc, "A sample plug-in that does nothing.");

  XPLMSpeakString("empty plugin start");

  g_menu_container_idx =
      XPLMAppendMenuItem(XPLMFindPluginsMenu(), "Sample Menu", 0, 0);

  g_menu_id = XPLMCreateMenu("Sample Menu", XPLMFindPluginsMenu(),
                             g_menu_container_idx, menu_handler, NULL);

  XPLMAppendMenuItem(g_menu_id, "Toggle Settings", (void *)"Menu Item 1", 1);

  XPLMAppendMenuSeparator(g_menu_id);

  XPLMAppendMenuItem(g_menu_id, "Toggle Shortcuts", (void *)"Menu Item 2", 1);
  XPLMAppendMenuItemWithCommand(
      g_menu_id, "Toggle Flight Configuration (Command-Based)",
      XPLMFindCommand("sim/operation/toggle_flight_config"));

  return 1;
}

PLUGIN_API void XPluginStop(void) { XPLMSpeakString("empty plugin stop"); }

PLUGIN_API void XPluginDisable(void) {
  XPLMSpeakString("empty plugin disable");
}
PLUGIN_API int XPluginEnable(void) {
  XPLMSpeakString("empty plugin enable");
  return 1;
}
PLUGIN_API void XPluginReceiveMessage(XPLMPluginID inFrom, int inMsg,
                                      void *inParam) {
  (void)inFrom;
  (void)inMsg;
  (void)inParam;
}

void menu_handler(void *in_menu_ref, void *in_item_ref) {
  (void)in_menu_ref;
  (void)in_item_ref;

  if (!strcmp((const char *)in_item_ref, "Menu Item 1")) {
    XPLMCommandOnce(XPLMFindCommand("sim/operation/toggle_settings_window"));
  } else if (!strcmp((const char *)in_item_ref, "Menu Item 2")) {
    XPLMCommandOnce(
        XPLMFindCommand("sim/operation/toggle_key_shortcuts_window"));
  }
}
