import QtQuick 2.0
import StyleSettings 1.0

Rectangle {
    id:root

    border.width: 1
    border.color: "red"

    radius: width / 2

    property alias image: _image
    RoundImageSub {
        id: _image
        anchors.fill: parent
        anchors.margins: Style.basicMargin
    }
}
