import QtQuick 2.0
import QtGraphicalEffects 1.0

Image{
    id:root

    sourceSize.width: width
    sourceSize.height: height

    layer.enabled: true
    layer.effect: OpacityMask{
        maskSource: Item{
            width: root.width
            height: root.height

            Rectangle{
                anchors.fill: parent
                radius: width / 2
            }
        }
    }


}
