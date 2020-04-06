#include "ProjectsModel.h"
#include <QQmlEngine>

ProjectsModel::ProjectsModel(QObject *parent)
    :QAbstractListModel(parent)
{
    ProjectInfo info("project1", 1, 1, {}, "", {1,30,00}, {10,45,33}, {25,28,44});
    m_projects.push_back(info);
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

    ProjectInfo info = m_projects[index.row()];

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

        case ProjectRoles::WatchUsersRole:
        {
            return QVariant::fromValue(info.watchUsers());
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

QHash<int, QByteArray> ProjectsModel::roleNames() const
{
    QHash<int, QByteArray> roles;
    roles[ProjectRoles::ProjectNameRole] = "projectName";
    roles[ProjectRoles::IsActiveRole] = "isActive";
    roles[ProjectRoles::IsWatcherRole] = "isWatcher";
    roles[ProjectRoles::WatchUsersRole] = "watchUsers";
    roles[ProjectRoles::IconUrlRole] = "iconUrl";
    roles[ProjectRoles::TimeThisWeekRole] = "timeThisWeek";
    roles[ProjectRoles::TimeThisMonthRole] = "timeThisMonth";
    roles[ProjectRoles::TimeTotalRole] = "timeTotal";
    return roles;
}

void ProjectsModel::onReadProjectsInfo()
{

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

void ProjectsModel::addData(const ProjectInfo &info)
{
    m_projects.push_back(info);
}
