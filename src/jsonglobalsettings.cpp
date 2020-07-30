#include "jsonglobalsettings.h"

#include "jsonsettingsfile.h"

#include <QDebug>

JsonGlobalSettings::JsonGlobalSettings(QQuickItem *t_parent) :
  QQuickItem(t_parent),
  m_settings(JsonSettingsFile::getInstance())
{
  connect(m_settings,&JsonSettingsFile::settingsChanged, this, &JsonGlobalSettings::sigSettingsChanged);
}

JsonSettingsFile *JsonGlobalSettings::globalSettings() const
{
  return m_settings;
}
