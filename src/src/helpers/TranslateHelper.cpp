#include "helpers/TranslateHelper.h"

#include <QGuiApplication>
#include <QQmlEngine>

#include "helpers/settingshelper.h"

[[maybe_unused]] TranslateHelper::TranslateHelper(QObject *parent) : QObject(parent) {
    _languages << "en_US";
    _languages << "zh_CN";
    _current = "zh_CN";
}

TranslateHelper::~TranslateHelper() = default;

void TranslateHelper::init(QQmlEngine *engine) {
    _engine = engine;
    _translator = new QTranslator(this);
    QGuiApplication::installTranslator(_translator);
    QString translatorPath = ":/i18n/";
    if (_translator->load(
            QString::fromStdString("%1/%2.qm").arg(translatorPath, _current))) {
        _engine->retranslate();
    }
}
