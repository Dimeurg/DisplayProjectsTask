import QtQuick 2.0
import DisplayModule.Base 1.0
import ServerModule 1.0

BaseListView{
    id: root

    model: globalProjectsModel
    spacing: 5

    delegate: ProjectsListDelegate{
        height: 100
        width: root.width

        MouseArea{
            anchors.fill: parent
            onClicked: {

                _infoDialog.projectInfo = globalProjectsModel.getProjectInfo(index)
                _infoDialog.open()
            }
        }
    }

    ProjectInfoDialog{
        id: _infoDialog
    }
}
