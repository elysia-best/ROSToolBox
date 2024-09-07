#include "helpers/settingshelper.h"

#include <QFile>
#include <iostream>

SettingsHelper::SettingsHelper(QObject* parent) : QObject{parent} {}
SettingsHelper::~SettingsHelper() = default;

void SettingsHelper::init() {
  const QString iniFileName = "ROSToolBoxConfig.ini";
  const QString iniFilePath =
      QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation) +
      "/ROSToolBoxConfig/" + iniFileName;

  std::cout << "Using config file: " << iniFilePath.toStdString() << std::endl;
  m_settings = std::make_shared<QSettings>(iniFilePath, QSettings::IniFormat);
}

void SettingsHelper::save(const QString& key, QVariant val) {
  m_settings->setValue(key, val);
  // setValue只是把配置项写入了缓冲区，若要写入文件，还需执行同步
  // 不同步，无法写入文件，无法生成文件
  m_settings->sync();
}

QVariant SettingsHelper::get(const QString& key, QVariant def) {
  QVariant data = m_settings->value(key);
  if (!data.isNull() && data.isValid()) {
    return data;
  }
  return def;
}

bool SettingsHelper::setIntData(const QString& KeyName, const int& value) {
  try {
    save(KeyName, value);
  } catch (...) {
    qWarning() << "Error saving Data:" << KeyName << " " << value;
    return false;
  }

  return true;
}

int SettingsHelper::getIntData(const QString& KeyName, const int& defValue) {
  return get(KeyName, QVariant(defValue)).toInt();
}

bool SettingsHelper::setBoolData(const QString& KeyName, const bool& value) {
  try {
    save(KeyName, value);
  } catch (...) {
    qWarning() << "Error saving Data:" << KeyName << " " << value;
    return false;
  }

  return true;
}

bool SettingsHelper::getBoolData(const QString& KeyName, const bool& defValue) {
  return get(KeyName, QVariant(defValue)).toBool();
}

bool SettingsHelper::setDoubleData(const QString& KeyName,
                                   const double& value) {
  try {
    save(KeyName, value);
  } catch (...) {
    qWarning() << "Error saving Data:" << KeyName << " " << value;
    return false;
  }

  return true;
}

double SettingsHelper::getDoubleData(const QString& KeyName,
                                     const double& defValue) {
  return get(KeyName, QVariant(defValue)).toDouble();
}

bool SettingsHelper::setStringData(const QString& KeyName,
                                   const QString& value) {
  try {
    save(KeyName, value);
  } catch (...) {
    qWarning() << "Error saving Data:" << KeyName << " " << value;
    return false;
  }

  return true;
}

QString SettingsHelper::getStringData(const QString& KeyName,
                                      const QString& defValue) {
  return get(KeyName, QVariant(defValue)).toString();
}
