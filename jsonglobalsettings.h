#ifndef JSONGLOBALSETTINGS_H
#define JSONGLOBALSETTINGS_H

#include <QQuickItem>

class JsonSettingsFile;

class JsonGlobalSettings : public QQuickItem
{
  Q_OBJECT
  Q_PROPERTY(JsonSettingsFile* globalSettings READ globalSettings NOTIFY settingsChanged)
public:
  explicit JsonGlobalSettings(QQuickItem *parent = 0);

  JsonSettingsFile* globalSettings() const;

signals:
  void settingsChanged(JsonSettingsFile* arg);

public slots:

private:
  JsonSettingsFile* m_settings;
};

#endif // JSONGLOBALSETTINGS_H
