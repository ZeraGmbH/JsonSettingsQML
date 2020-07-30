#include "jsonsettings_plugin.h"
#include <qqml.h>

#include "jsonglobalsettings.h"
#include "jsonsettingsfile.h"


void JsonSettingsPlugin::init()
{
    JsonSettingsPlugin* obj= new JsonSettingsPlugin();
    obj->registerTypes("ZeraSettings");
}


void JsonSettingsPlugin::registerTypes(const char *t_uri)
{
  // @uri JsonSettings
  qmlRegisterType<JsonSettingsFile>(t_uri, 1, 0, "ZeraSettings");
  qmlRegisterType<JsonGlobalSettings>(t_uri, 1, 0, "ZeraGlobalSettings");
}


static void init(){
    JsonSettingsPlugin::init();
}
Q_COREAPP_STARTUP_FUNCTION(init)
