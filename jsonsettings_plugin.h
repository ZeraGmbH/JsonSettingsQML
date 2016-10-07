#ifndef JSONSETTINGS_PLUGIN_H
#define JSONSETTINGS_PLUGIN_H

#include <QQmlExtensionPlugin>

class JsonSettingsPlugin : public QQmlExtensionPlugin
{
  Q_OBJECT
  Q_PLUGIN_METADATA(IID "org.qt-project.Qt.QQmlExtensionInterface")

public:
  void registerTypes(const char *t_uri);
};

#endif // JSONSETTINGS_PLUGIN_H

