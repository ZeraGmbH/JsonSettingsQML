#ifndef JSONGLOBALSETTINGS_H
#define JSONGLOBALSETTINGS_H

#include <QQuickItem>

class JsonSettingsFile;

class JsonGlobalSettings : public QQuickItem
{
  Q_OBJECT
  Q_PROPERTY(JsonSettingsFile *globalSettings READ globalSettings NOTIFY sigSettingsChanged)
public:
  explicit JsonGlobalSettings(QQuickItem *t_parent = 0);

  JsonSettingsFile *globalSettings() const;

signals:
  void sigSettingsChanged(JsonSettingsFile *settingsFile);

public slots:

private:
  JsonSettingsFile *m_settings;
};

#endif // JSONGLOBALSETTINGS_H
