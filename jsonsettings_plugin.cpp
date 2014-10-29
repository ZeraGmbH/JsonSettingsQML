#include "jsonsettings_plugin.h"
#include <qqml.h>

#include "jsonglobalsettings.h"
#include "jsonsettingsfile.h"

void JsonSettingsPlugin::registerTypes(const char *uri)
{
  // @uri JsonSettings
  qmlRegisterType<JsonSettingsFile>(uri, 1, 0, "JsonSettings");
  qmlRegisterType<JsonGlobalSettings>(uri, 1, 0, "JsonGlobalSettings");
}


