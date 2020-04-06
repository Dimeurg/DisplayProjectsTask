import QtQuick 2.0
import StyleSettings 1.0
import DisplayModule.Base 1.0
import QtQuick.Controls 2.12

Rectangle{
    id:root
    color: Style.backgroundColor

    property alias logButton: _logButton
    property alias email: _email
    property alias password: _password

    function onError(error)
    {
        var message = ""
        for (var key in error) {
            if (error.hasOwnProperty(key)) {
                message += ("Error: " + error[key] + "<br>")
            }
        }

        _errLabel.text = message
    }

    Column{
        width: root /2
        anchors.centerIn: parent

        BaseText{
            text: "LOGIN"
        }

        TextEdit{
            id: _email
            width: parent.width
            height: 30

            font.pointSize: 13
            color: Style.textColor

            BaseText {
                text: "Email"
                color: "#aaa"
                visible: !parent.text
            }
        }

        TextEdit{
            id: _password
            width: parent.width
            height: 30

            color: Style.textColor
            font.pointSize: 13

            BaseText {
                text: "Password"
                color: "#aaa"
                visible: !parent.text
            }
        }

        Button{
            id: _logButton
            text: "LOGIN"
        }

        Label{
            id: _errLabel
            text: ""
            color: "red"
        }
    }


}
