#ifndef JSONSETTINGSFILE_H
#define JSONSETTINGSFILE_H

#include <QQuickItem>

class JsonSettingsFilePrivate;

class JsonSettingsFile : public QQuickItem
{
  Q_OBJECT
public:
  explicit JsonSettingsFile(QQuickItem *parent = 0);

  static JsonSettingsFile* getInstance();

  Q_INVOKABLE bool fileExists(const QString &filePath) const;
  Q_INVOKABLE void reloadFile();
  Q_INVOKABLE bool loadFromStandardLocation(const QString &fileName);
  Q_INVOKABLE bool loadFromFile(const QString &filePath);
  Q_INVOKABLE void saveToFile(const QString &filePath, bool overwrite=false);
  Q_INVOKABLE const QString &getCurrentFilePath();

  Q_INVOKABLE bool hasOption(const QString &key);
  Q_INVOKABLE QString getOption(const QString &key);
  Q_INVOKABLE bool setOption(const QString &key, QString value, bool addIfNotExists=false);
  Q_INVOKABLE bool dropOption(const QString &key);

signals:
  void settingsChanged(JsonSettingsFile* arg);

public slots:

private:
  JsonSettingsFilePrivate *d_ptr;

  static JsonSettingsFile* globalSettings;

  Q_DECLARE_PRIVATE(JsonSettingsFile)
  Q_DISABLE_COPY(JsonSettingsFile)
};

#endif // JSONSETTINGSFILE_H
