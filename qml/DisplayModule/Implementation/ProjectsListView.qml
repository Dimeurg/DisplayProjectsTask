import QtQuick 2.0
import DisplayModule.Base 1.0
import ProjectsModel 1.0
import ServerModule 1.0

BaseListView{
    id: root

    function setToken(token)
    {
        root.model.token = token
    }

    model: ProjectsModel{
        onTokenChanged: {
            onReadProjectsInfo(Server.getProjectsInfo(token))
        }
    }

    delegate: ProjectsListDelegate{
        height: 100
        width: root.width

        MouseArea{
            anchors.fill: parent
            onClicked: {
                var projectInfo

                _infoDialog.projectInfo = root.model.getProjectInfo(index)
                _infoDialog.token = root.model.token

                _infoDialog.open()
            }
        }
    }

    ProjectInfoDialog{
        id: _infoDialog

    }
}
