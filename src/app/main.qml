import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick.Window

ApplicationWindow {
    id: root
    visible: true
    width: 960
    height: 540
    title: qsTr("Foo Application")

    FontLoader { id: idFont; source: "qrc:/font/Roboto-Regular.ttf"}
    FontLoader { source: "qrc:/font/Roboto-Thin.ttf"}
    FontLoader { source: "qrc:/font/Roboto-Light.ttf"}
    FontLoader { source: "qrc:/font/Roboto-Medium.ttf"}
    FontLoader { source: "qrc:/font/Roboto-Bold.ttf"}
    FontLoader { source: "qrc:/font/Roboto-Black.ttf"}

    font.family: idFont.name
    font.weight: Font.Normal
    font.pointSize: 9
    font.letterSpacing: 1.2
}
