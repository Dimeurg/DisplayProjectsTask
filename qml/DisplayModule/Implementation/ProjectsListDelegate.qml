import QtQuick 2.0
import DisplayModule.Base 1.0
import StyleSettings 1.0

BaseListDelegate{
    id: root
        Row{
            id: _row1
            width: root.width / 2
            height: root.height

            RoundImage{
                id: _image
                width: parent.height
                height: width
                image.source: iconUrl
            }

            Row{
                id: _projectName
                height: parent.height
                width: parent.width - _image.width
                BaseText{
                    anchors.centerIn: parent
                    text: projectName
                }
            }
        }

        Row{
            id: _row2
            width: root.width / 2
            height: root.height
            anchors.left: _row1.right

            Row{
                id: _textActive
                width: parent.width /3
                height: parent.height

                BaseText{
                    anchors.centerIn: parent
                    text: isActive ? "Active" : "Inactive"
                    color: Style.basicColor
                }
            }

            Column{
                id: _columnTimeLable
                width: parent.width /3
                height: parent.height

                BaseText{
                    text: "time this week"
                }

                BaseText{
                    text: "this month"
                }

                BaseText{
                    text: "total"
                }
            }

            Column{
                id: _columnTime
                width: parent.width /3
                height: parent.height

                BaseText{
                    text: timeThisWeek
                }

                BaseText{
                    text: timeThisMonth
                }

                BaseText{
                    text: timeTotal
                }
            }
        }
}
