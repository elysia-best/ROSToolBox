#include <QApplication>
#include <QGuiApplication>
#include <QProcess>
#include <QQmlApplicationEngine>

#include "components/CircularReveal.h"
#include "helpers/TranslateHelper.h"
#include "helpers/settingshelper.h"

int main(int argc, char *argv[]) {
#if QT_VERSION < QT_VERSION_CHECK(6, 0, 0)
  QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
  QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
#endif
#if (QT_VERSION >= QT_VERSION_CHECK(5, 14, 0))
  QApplication::setHighDpiScaleFactorRoundingPolicy(
      Qt::HighDpiScaleFactorRoundingPolicy::PassThrough);
#endif

  QApplication::setOrganizationName("Elysia");
  QApplication::setOrganizationDomain("rostoolbox.qinyn.eu.org");
  QApplication::setApplicationName("ROSToolBox");
  QApplication::setApplicationDisplayName("ROSToolBox");
  QApplication::setApplicationVersion("1.0.0");
  QApplication::setQuitOnLastWindowClosed(false);

  QGuiApplication app(argc, argv);

  SettingsHelper::getInstance()->init();

  qmlRegisterType<CircularReveal>("ROSToolBox", 1, 0, "CircularReveal");

  QQmlApplicationEngine engine;

  TranslateHelper::getInstance()->init(&engine);

  engine.rootContext()->setContextProperty("SettingsHelper",
                                           SettingsHelper::getInstance());
  engine.rootContext()->setContextProperty("TranslateHelper",
                                           TranslateHelper::getInstance());

  const QUrl url(QStringLiteral("qrc:/qml/main.qml"));
  QObject::connect(
      &engine, &QQmlApplicationEngine::objectCreated, &app,
      [url](QObject *obj, const QUrl &objUrl) {
        if (!obj && url == objUrl) QCoreApplication::exit(-1);
      },
      Qt::QueuedConnection);
  engine.load(url);

  const int exec = QApplication::exec();
  if (exec == 931) {
    QProcess::startDetached(qApp->applicationFilePath(), qApp->arguments());
  }
  return exec;
}
