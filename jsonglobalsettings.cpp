#include "jsonglobalsettings.h"

#include "jsonsettingsfile.h"

#include <QDebug>

JsonGlobalSettings::JsonGlobalSettings(QQuickItem *parent) :
  QQuickItem(parent),
  m_settings(JsonSettingsFile::getInstance())
{
  connect(m_settings,&JsonSettingsFile::settingsChanged, this, &JsonGlobalSettings::settingsChanged);
}

JsonSettingsFile *JsonGlobalSettings::globalSettings() const
{
  return m_settings;
}
