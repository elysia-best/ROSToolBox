import QtQuick 2.15
import QtQuick.Window 2.15
import FluentUI 1.0

FluLauncher {
    id: app

    Connections {
        target: FluTheme
        function onDarkModeChanged(){
            SettingsHelper.setBoolData("darkMode", FluTheme.darkMode);
        }
    }

    Connections {
        target: FluApp
        function onUseSystemAppBarChanged(){
            SettingsHelper.setBoolData("useSystemAppBar", FluApp.useSystemAppBar);
        }
    }

    Connections{
        target: TranslateHelper
        function onCurrentChanged(){
            SettingsHelper.setStringData("language", TranslateHelper.current);
        }
    }

    Component.onCompleted: {
        FluApp.init(app, Qt.locale(TranslateHelper.current));
        FluApp.useSystemAppBar = SettingsHelper.getBoolData("useSystemAppBar", false);

        if (SettingsHelper.getBoolData("darkMode", true)) {
            FluTheme.darkMode = FluThemeType.Dark;
        } else {
            FluTheme.darkMode = FluThemeType.Light;
        }

        FluTheme.animationEnabled = true;

        app.m_registerRoutes();
        FluRouter.navigate("/");
    }

    function m_registerRoutes() {
        FluRouter.routes = {
            "/": "qrc:/qml/windows/mainwindow.qml"
        };
    }
}
