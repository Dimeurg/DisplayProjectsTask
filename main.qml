import QtQuick 2.12
import QtQuick.Window 2.12
import DisplayModule.Implementation 1.0
import QtQuick.Controls 2.12

import ServerModule 1.0

ApplicationWindow {
    id:root
    visible: true
    width: 640
    height: 480
    title: "Projects viewer"

    Rectangle{
        id: _menu

        anchors.top: parent.top
        width:parent.width
        height: 40
        color: "#aaa"

        Button{
            id: _logoutButton
            height: parent.height
            anchors.right: parent.right

            visible: false
            text: "LOGOUT"

            onClicked: {
                _swipeView.currentIndex = _swipeView.loginPage
                globalProjectsModeltoken = ""
                visible: false
            }
        }
    }

    SwipeView {
        id: _swipeView

        anchors.top: _menu.bottom
        width: parent.width
        height: parent.height - _menu.height
        property int loginPage : 0     // index for Login page
        property int projectsPage : 1  // index for Projects page

        Component.onCompleted: contentItem.interactive = false

        ProjectsLoginView{
            id: _loginPage
            width: _swipeView.width
            height: _swipeView.height

            onLogged: {
                _logoutButton.visible = true
                _swipeView.currentIndex = _swipeView.projectsPage
            }
        }

        ProjectsListView{
            id: _projectsPage
            width: _swipeView.width
            height: _swipeView.height
        }
    }
}
