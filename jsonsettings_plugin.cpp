#include "jsonsettings_plugin.h"
#include <qqml.h>

#include "jsonglobalsettings.h"
#include "jsonsettingsfile.h"

void JsonSettingsPlugin::registerTypes(const char *t_uri)
{
  // @uri JsonSettings
  qmlRegisterType<JsonSettingsFile>(t_uri, 1, 0, "JsonSettings");
  qmlRegisterType<JsonGlobalSettings>(t_uri, 1, 0, "JsonGlobalSettings");
}


