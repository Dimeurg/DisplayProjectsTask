import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.12
import DisplayModule.Base 1.0
import StyleSettings 1.0

import ServerModule 1.0

Dialog {
    id:root

    implicitWidth: 700
    implicitHeight: 600

    standardButtons: StandardButton.Cancel | StandardButton.Ok

    property alias data: _data
    property alias changeNameButton: _changeNameButton
    property alias projectName: _projectName
    QtObject{
        id: _data

        property int index: 0
        property bool isActive: false
        property bool isWatcher: false
        property string projectName: ""
        property string projectIconSource: ""
    }

    contentItem: Rectangle {
        anchors.fill: parent
        color: Style.backgroundColor

        Column{
            anchors.fill: parent
            Row{
                id: _row1
                width: parent.width
                height: parent.height / 3
                anchors.top: parent.top
                Column{
                    id: _column1
                    width: parent.width / 2
                    height: parent.height

                    Row{
                        id: _aaa
                        spacing: 5
                        width: parent.width
                        height: parent.height / 2

                        BaseText{
                            anchors.verticalCenter: parent.verticalCenter
                            text: "Active"}
                        BaseText{
                            anchors.verticalCenter: parent.verticalCenter
                            text: _data.isActive? "Active": "Unactive"}
                    }

                    Row{
                        spacing: 5
                        width: parent.width
                        height: parent.height / 2
                        anchors.top: _aaa.bottom

                        BaseText{
                            id: _labelName
                            anchors.verticalCenter: parent.verticalCenter
                            text: "Name"}

                        Rectangle
                        {
                            anchors.verticalCenter: parent.verticalCenter
                            anchors.left: _labelName.right
                            anchors.leftMargin: Style.mediumOffset
                            anchors.right: parent.right
                            height: parent.height / 2
                            color: "white"
                            TextInput{
                                id: _projectName
                                text: _data.projectName
                                color: "#aaa"
                                font.pointSize: 13

                            }
                        }


                    }
                }

                Button{
                    id: _changeNameButton
                    anchors.left: _column1.right
                    anchors.leftMargin: Style.mediumOffset
                    anchors.bottom: parent.bottom
                    anchors.bottomMargin: Style.mediumOffset

                    text: "OK"
                }

                RoundImage{

                    width: parent.height / 2
                    height: width
                    anchors.right: parent.right
                    anchors.rightMargin: Style.mediumOffset
                    anchors.verticalCenter: parent.verticalCenter
                    image.source: _data.projectIconSource
                }
            }

            Row{
                id: _row2
                width: parent.width
                height: parent.height / 3
                anchors.top: _row1.bottom

                BaseText
                {
                    anchors.verticalCenter: parent.verticalCenter
                    text: "Users"
                }
            }

            Row{
                id: _row3
                width: parent.width
                anchors.top: _row2.bottom
                anchors.bottom: parent.bottom

                BaseText
                {
                    verticalAlignment: Text.verticalCenter
                    text: _data.isWatcher ? "Watcher" : "Not Watcher"
                }
            }
        }
    }
}


