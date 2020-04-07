#include "ProjectsModel.h"
#include "Parser.h"
#include <QQmlEngine>
#include <QPointer>

ProjectsModel::ProjectsModel(QObject *parent)
    :QAbstractListModel(parent)
{

}

ProjectsModel::~ProjectsModel()
{

}

void ProjectsModel::registerMe(const std::string &moduleName)
{
    qmlRegisterType<ProjectsModel>(moduleName.c_str(), 1, 0, "ProjectsModel");
}

int ProjectsModel::rowCount(const QModelIndex &parent) const
{
    Q_UNUSED(parent)
    return m_projects.size();
}

QVariant ProjectsModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid() || index.row() > rowCount())
    {
        return QVariant();
    }

    const ProjectInfo& info = *(m_projects[index.row()].get());

    switch(role)
    {
        case ProjectRoles::ProjectNameRole:
        {
            return QVariant::fromValue(info.projectName());
            break;
        }

        case ProjectRoles::IsActiveRole:
        {
            return QVariant::fromValue(info.isActive());
            break;
        }

        case ProjectRoles::IsWatcherRole:
        {
            return QVariant::fromValue(info.isWatcher());
            break;
        }

        case ProjectRoles::UsersRole:
        {
            return QVariant::fromValue(info.users());
            break;
        }

        case ProjectRoles::IconUrlRole:
        {
            return QVariant::fromValue(info.iconUrl());
            break;
        }

        case ProjectRoles::TimeThisWeekRole:
        {
            return QVariant::fromValue(info.timeThisWeek().toString());
            break;
        }

        case ProjectRoles::TimeThisMonthRole:
        {
            return QVariant::fromValue(info.timeThisMonth().toString());
            break;
        }

        case ProjectRoles::TimeTotalRole:
        {
            return QVariant::fromValue(info.timeTotal().toString());
            break;
        }

        default:
        {
            return QVariant();
        }
    }
}

void ProjectsModel::onProjectNameChanged()
{
     dataChanged(createIndex(0, 0), createIndex(m_projects.size(), 0));
}

QVariant ProjectsModel::getProjectInfo(int index) const
{
    if(index >= rowCount() || index < 0)
        return QVariant();

    return QVariant::fromValue(m_projects[index].get());
}

QHash<int, QByteArray> ProjectsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ProjectRoles::ProjectNameRole] = "projectName";
    roles[ProjectRoles::IsActiveRole] = "isActive";
    roles[ProjectRoles::IsWatcherRole] = "isWatcher";
    roles[ProjectRoles::UsersRole] = "users";
    roles[ProjectRoles::IconUrlRole] = "iconUrl";
    roles[ProjectRoles::TimeThisWeekRole] = "timeThisWeek";
    roles[ProjectRoles::TimeThisMonthRole] = "timeThisMonth";
    roles[ProjectRoles::TimeTotalRole] = "timeTotal";
    return roles;
}

void ProjectsModel::onReadProjectsInfo(const QJsonArray& projectsInfo)
{
    //update data
    beginResetModel();
    Parser::projectsInfoParse(projectsInfo, m_projects);
    endResetModel();

    for(auto& projectInfo: m_projects)
    {
        connect(projectInfo.get(), &ProjectInfo::projectNameChanged, this, &ProjectsModel::onProjectNameChanged);
    }
}

QString ProjectsModel::token() const
{
    return m_token;
}

void ProjectsModel::setToken(const QString &token)
{
    if(m_token != token)
    {
        m_token = token;
        emit tokenChanged();
    }
}

