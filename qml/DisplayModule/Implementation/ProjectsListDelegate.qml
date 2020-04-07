import QtQuick 2.0
import DisplayModule.Base 1.0
import StyleSettings 1.0

BaseListDelegate{
    id: root

    property bool thisIsActive: isActive

    RoundImage{
        id: _icon
        width: Math.min(parent.width / 8, parent.height - Style.basicMargin)
        height: width
        image.source: iconUrl

        anchors.left: parent.left
        anchors.leftMargin: Style.mediumOffset
        anchors.verticalCenter: parent.verticalCenter
    }

    BaseText{
        id: _projectName
        anchors.left: _icon.right
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width / 3
        height: parent.height / 3

        horizontalAlignment: TextInput.AlignHCenter
        text: projectName
    }


    BaseText{
        id: _isActive
        anchors.left: _projectName.right
        anchors.verticalCenter: parent.verticalCenter
        width: parent.width / 8
        height: parent.height / 3

        horizontalAlignment: TextInput.AlignHCenter
        text: isActive ? "Active" : "Inactive"
        color: isActive ? "green" : "red"
    }

    BaseText{
        id: _timeThisWeekLabel

        anchors.left: _isActive.right
        anchors.leftMargin: Style.mediumOffsetf
        anchors.top: parent.top
        width: parent.width/4
        height: parent.height/3

        text: "time this week"
    }

    BaseText{
        id: _timeThisMonthLabel

        anchors.left: _timeThisWeekLabel.left
        anchors.top: _timeThisWeekLabel.bottom
        width: parent.width/4
        height: parent.height/3

        text: "this month"
    }

    BaseText{
        id: _timeTotalLabel

        anchors.left: _timeThisWeekLabel.left
        anchors.top: _timeThisMonthLabel.bottom
        width: parent.width/4
        height: parent.height/3

        text: "total"
    }

    BaseText{
        anchors.left: _timeThisWeekLabel.right
        anchors.top: _timeThisWeekLabel.top

        anchors.right: parent.right
        text: timeThisWeek
    }

    BaseText{
        anchors.left: _timeThisMonthLabel.right
        anchors.top: _timeThisMonthLabel.top

        anchors.right: parent.right
        text: timeThisMonth
    }

    BaseText{
        anchors.left: _timeTotalLabel.right
        anchors.top: _timeTotalLabel.top

        anchors.right: parent.right
        text: timeTotal
    }

}


