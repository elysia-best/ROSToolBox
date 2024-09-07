/*
 * (C) Copyright 2024 赤い月 All Rights Reserved.
 * Description：
 * Author：赤い月
 * Date: 2024/2/11
 * Modify Record:
 */
#ifndef SETTINGSHELPER_H
#define SETTINGSHELPER_H

#include <memory>

#include <QCoreApplication>
#include <QDir>
#include <QFileInfo>
#include <QMetaObject>
#include <QObject>
#include <QScopedPointer>
#include <QSettings>
#include <QtQml>
#include "singleton.h"

class SettingsHelper : public QObject {
  Q_OBJECT
 private:
  explicit SettingsHelper(QObject* parent = nullptr);

 public:
  SINGLETON(SettingsHelper)

  ~SettingsHelper() override;

  void init();

  Q_INVOKABLE bool setIntData(const QString& KeyName, const int& value);

  Q_INVOKABLE int getIntData(const QString& KeyName, const int& defValue);

  Q_INVOKABLE bool setBoolData(const QString& KeyName, const bool& value);

  Q_INVOKABLE bool getBoolData(const QString& KeyName, const bool& defValue);

  Q_INVOKABLE bool setDoubleData(const QString& KeyName, const double& value);

  Q_INVOKABLE double getDoubleData(const QString& KeyName,
                                   const double& defValue);

  Q_INVOKABLE bool setStringData(const QString& KeyName, const QString& value);

  Q_INVOKABLE QString getStringData(const QString& KeyName,
                                    const QString& defValue);

 private:
  void save(const QString& key, QVariant val);

  /**
   * @brief 获取设置
   *
   * @param key: 设置项名称
   * @param def: 默认值
   */
  QVariant get(const QString& key, QVariant def = {});

  std::shared_ptr<QSettings> m_settings;
};

#endif  // SETTINGSHELPER_H
