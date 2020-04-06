import QtQuick 2.0
import StyleSettings 1.0

Rectangle{
    id:root

    border.width: 1
    border.color: Style.basicColor

    radius: width / 2

    property alias image: _image
    Image{
        id: _image
        anchors.fill: parent

        sourceSize.width: width
        sourceSize.height: height
    }
}
