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

    SwipeView {
        id: _swipeView
        anchors.fill: parent
        property int loginPage : 0     // index for Login page
        property int projectsPage : 1  // index for Projects page

        Component.onCompleted: contentItem.interactive = false

        Item
        {
            id: _loginPage
            ProjectsLoginView{
                id: _loginView
                width: root.width
                height: root.height

                logButton.onClicked: {
                    var result = Server.loginToServer(email.text, password.text)
                    if(typeof result === 'string')
                    {
                        _projectsPageView.setToken(result)
                        _swipeView.currentIndex = _swipeView.projectsPage

                        email.text = ""
                        password.text = ""
                    }

                    else
                    {
                        _loginView.onError(result)
                    }
                }

            }
        }

        Item{
            id: _projectsPage

            Rectangle{
                id: _menu

                width:parent.width
                height: 40
                color: "#aaa"

                Button{
                    id: _logoutButton
                    height: parent.height
                    anchors.right: parent.right

                    text: "LOGOUT"

                    onClicked: {
                        _swipeView.currentIndex = _swipeView.loginPage
                        _projectsPageView.model.token = ""
                    }
                }
            }

            ProjectsListView{
                id: _projectsPageView
                width: root.width
                height: root.height
                anchors.top: _menu.bottom
            }
        }
    }
}
