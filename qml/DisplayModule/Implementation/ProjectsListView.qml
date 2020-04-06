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

        onProjectNameChanged: {
            Server.changeName(token, id, name)
        }
    }

    delegate: ProjectsListDelegate{
        height: 100
        width: root.width


        MouseArea{
            anchors.fill: parent
            onClicked: {
                _infoDialog.data.index = index
                _infoDialog.data.projectName = root.model.getName(index)
                _infoDialog.data.isActive = root.model.getIsActive(index)
                _infoDialog.data.isWatcher = root.model.getIsWatcher(index)
                _infoDialog.data.projectIconSource = root.model.getIconUrl(index)

                _infoDialog.open()
            }
        }
    }

    ProjectInfoDialog{
        id: _infoDialog

        changeNameButton.onClicked:  {
            root.model.setName(data.index, projectName.text)
        }
    }
}
