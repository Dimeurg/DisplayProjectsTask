import QtQuick 2.0
import StyleSettings 1.0
import DisplayModule.Base 1.0
import QtQuick.Controls 2.12
import ServerModule 1.0

Rectangle{
    id:root
    color: Style.backgroundColor

    property alias logButton: _logButton
    property alias email: _email
    property alias password: _password

    signal logged()

    BaseText{
        id: _loginLable
        anchors.top: parent.top
        anchors.topMargin: parent.height / 4
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width / 8
        height: parent.height / 14
        text: "LOGIN"
    }

    TextField {
        id: _email

        anchors.top: _loginLable.bottom
        anchors.topMargin: Style.mediumOffset
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width / 3
        height: _loginLable.height

        placeholderText: "Email"
        font.pointSize: 13
        color: Style.backgroundColor


        background: Rectangle {
            implicitWidth: parent.width
            implicitHeight: 30
            color: Style.basicColor
            border.color: Style.basicColor
        }
    }

    TextField {
        id: _password

        echoMode: TextField.Password

        anchors.top: _email.bottom
        anchors.topMargin: Style.mediumOffset
        anchors.horizontalCenter: parent.horizontalCenter
        width: parent.width / 3
        height: _loginLable.height

        placeholderText: "Password"

        font.pointSize: 13
        color: Style.backgroundColor

        background: Rectangle {
            implicitWidth: parent.width
            implicitHeight: 30
            color: Style.basicColor
            border.color: Style.basicColor
        }
    }

    Button{
        id: _logButton

        anchors.top: _password.bottom
        anchors.topMargin: Style.mediumOffset
        anchors.horizontalCenter: parent.horizontalCenter

        text: "LOGIN"

        onClicked: {
            Server.loginToServer()
            var result = Server.loginToServer(_email.text, _password.text)
            if(typeof result === 'string')
            {
                globalProjectsModel.token = result
                logged()

                email.text = ""
                password.text = ""

                globalProjectsModel.onReadProjectsInfo(Server.getProjectsInfo(globalProjectsModel.token))
            }

            else
            {
                var message = ""
                for (var key in result) {
                    if (result.hasOwnProperty(key)) {
                        message += ("Error: " + result[key] + "<br>")
                    }
                }

                _errLabel.text = message
            }
        }

    }

    Label{
        id: _errLabel

        anchors.top: _logButton.bottom
        anchors.topMargin: Style.mediumOffset
        anchors.horizontalCenter: parent.horizontalCenter

        color: "red"
    }
}
