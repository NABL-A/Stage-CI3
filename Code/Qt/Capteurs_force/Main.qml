import QtQuick
import QtQuick.Controls
import QtQuick.Layouts
import QtQuick3D

ApplicationWindow {
    visible: true
    width: 1200
    height: 600
    title: "Sensors Gaussian Viewer"

    RowLayout {
        anchors.fill: parent

        Gaussian2DView {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }

        Gaussian3DView {
            Layout.fillWidth: true
            Layout.fillHeight: true
        }
    }
}