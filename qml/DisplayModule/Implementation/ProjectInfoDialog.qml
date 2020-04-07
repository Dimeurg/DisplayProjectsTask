import QtQuick 2.0
import QtQuick.Dialogs 1.2
import QtQuick.Controls 2.12
import DisplayModule.Base 1.0
import StyleSettings 1.0

import ServerModule 1.0
import ProjectInfo 1.0

Dialog {
    id:root

    implicitWidth: 700
    implicitHeight: 600

    standardButtons: StandardButton.Cancel | StandardButton.Ok

    property string token: ""

    property var projectInfo: ({})

    contentItem: Rectangle {
        anchors.fill: parent
        color: Style.backgroundColor

        BaseText
        {
            id: _activeLabel
            anchors.top: parent.top
            anchors.left: parent.left
            height: parent.height/8
            width: parent.width/4

            text: "Active: "
        }

        BaseText
        {
            id: _activeValue
            anchors.top: _activeLabel.top
            anchors.left: _activeLabel.right
            height: _activeLabel.height / 2
            width: parent.width/3
            text: projectInfo.isActive? "Active": "Unactive"
            color: projectInfo.isActive? "green": "red"
        }

        BaseText
        {
            id: _nameLabel
            anchors.top: _activeLabel.bottom
            anchors.left: parent.left
            height: _activeLabel.height
            width: _activeLabel.width
            text: "Name"
        }

        Rectangle
        {
            id: _projectNameRect
            anchors.left: _nameLabel.right
            anchors.top: _nameLabel.top
            width: _activeValue.width
            height: _activeValue.height
            color: Style.basicColor
            TextInput{
                id: _projectName
                anchors.fill: parent
                text: projectInfo.projectName
                color: "#aaa"
                font.pointSize: 13

            }
        }

        Button{
            id: _changeNameButton
            anchors.left: _projectNameRect.right
            anchors.bottom: _projectNameRect.bottom
            anchors.leftMargin: Style.mediumOffset

            text: "OK"

            onClicked:  {
                projectInfo.projectName = _projectName.text
                Server.changeName(root.token, projectInfo.id, projectInfo.projectName)
            }
        }

        RoundImage{
            width: parent.width / 8
            height: width
            anchors.left: _changeNameButton.right
            anchors.top: parent.top
            anchors.leftMargin: Style.mediumOffset
            anchors.topMargin: Style.mediumOffset

            image.source: projectInfo.iconUrl
        }

        Rectangle{
            id: _usersRect
            anchors.left: parent.left
            anchors.top: _nameLabel.bottom
            width: parent.width
            height: parent.height/4

            color: Style.backgroundColor

            BaseText
            {
                id: _usersLabel
                width: _activeLabel.width
                height:_activeLabel.height
                anchors.left: parent.left
                anchors.top: parent.top
                text: "Users"
            }
        }

        BaseText
        {
            id: _watcherLabel
            width: _activeLabel.width
            height: _activeLabel.height
            anchors.left: parent.left
            anchors.top: _usersRect.bottom
            text: "Watcher: "
        }

        BaseText
        {
            id: _watcherValue
            width: _activeValue.width
            height: _activeValue.height
            anchors.left: _watcherLabel.right
            anchors.top: _usersRect.bottom
            text: projectInfo.isWatcher ? "Watcher" : "Not Watcher"
            color: projectInfo.isWatcher? "green": "red"
        }
    }
}


