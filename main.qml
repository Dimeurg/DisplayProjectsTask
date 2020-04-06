import QtQuick 2.12
import QtQuick.Window 2.12
import DisplayModule.Implementation 1.0

Window {
    visible: true
    width: 640
    height: 480
    title: qsTr("Projects viewer")

    ProjectsListView{
        anchors.fill: parent
    }
}
