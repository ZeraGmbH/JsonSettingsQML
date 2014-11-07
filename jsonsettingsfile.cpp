#include "jsonsettingsfile.h"
#include <QJsonParseError>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonValue>
#include <QDebug>

class JsonSettingsFilePrivate {

  JsonSettingsFilePrivate(JsonSettingsFile* qPtr) : q_ptr(qPtr) {}

  JsonSettingsFile* q_ptr;
  QString settingsFilePath;

  QJsonObject dataHolder;

  Q_DECLARE_PUBLIC(JsonSettingsFile)
};



JsonSettingsFile::JsonSettingsFile(QQuickItem *parent) :
  QQuickItem(parent),
  d_ptr(new JsonSettingsFilePrivate(this))
{
}

JsonSettingsFile *JsonSettingsFile::getInstance()
{
  if(globalSettings==0)
  {
    globalSettings = new JsonSettingsFile();
  }
  return globalSettings;
}

void JsonSettingsFile::reloadFile()
{
  Q_D(JsonSettingsFile);
  loadFromFile(d->settingsFilePath);
}

void JsonSettingsFile::loadFromFile(const QString &filePath)
{
  Q_D(JsonSettingsFile);
  QFile f;
  f.setFileName(filePath);
  if(f.exists() && f.open(QFile::ReadOnly))
  {
    d->settingsFilePath = filePath;
    QJsonParseError err;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(f.readAll(), &err);
    if(err.error == QJsonParseError::NoError)
    {
      d->dataHolder = jsonDoc.object();
    }
    f.close();
    emit settingsChanged(this);
  }
  else
  {
    qDebug() << "[json-settings-qml] Settings file does not exists:" << filePath;
  }
}

void JsonSettingsFile::saveToFile(const QString &filePath, bool overwrite)
{
  Q_D(JsonSettingsFile);
  QFile f;
  f.setFileName(filePath);
  if(filePath.isEmpty() == false && (!f.exists() || overwrite) && f.open(QFile::WriteOnly))
  {
    QJsonDocument jsonDoc;
    jsonDoc.setObject(d->dataHolder);
    f.write(jsonDoc.toJson());
    f.close();
  }
}

const QString &JsonSettingsFile::getCurrentFilePath()
{
  Q_D(JsonSettingsFile);
  return d->settingsFilePath;
}

bool JsonSettingsFile::hasOption(const QString &key)
{
  Q_D(JsonSettingsFile);
  bool retVal=false;
  if(d->dataHolder.value(key) != QJsonValue::Undefined)
  {
    retVal = true;
  }
  return retVal;
}

QString JsonSettingsFile::getOption(const QString &key)
{
  Q_D(JsonSettingsFile);
  QString retVal;
  if(hasOption(key))
  {
    retVal = d->dataHolder.value(key).toString();
  }
  else
  {
    if(d->settingsFilePath.isEmpty() == false)
    {
      qDebug() << "[json-settings-qml] Could not find data for key:" << key;
    }
  }
  return retVal;
}

bool JsonSettingsFile::setOption(const QString &key, QString value, bool addIfNotExists)
{
  Q_D(JsonSettingsFile);
  bool retVal = false;
  if(hasOption(key) || addIfNotExists)
  {
    d->dataHolder.insert(key, value);
    retVal=true;
    emit settingsChanged(this);
  }
  else
  {
    qDebug() << "[json-settings-qml] Refused to set nonexisting key:" << key;
  }

  return retVal;
}

bool JsonSettingsFile::dropOption(const QString &key)
{
  Q_D(JsonSettingsFile);
  bool retVal = false;
  if(hasOption(key))
  {
    d->dataHolder.remove(key);
    retVal = true;
    emit settingsChanged(this);
  }
  else
  {
    qDebug() << "[json-settings-qml] Refused to delete nonexistant key:" << key;
  }

  return retVal;
}

JsonSettingsFile *JsonSettingsFile::globalSettings = 0;
