#include "ProjectsModel.h"
#include <QQmlEngine>
#include <QJsonArray>
#include <QJsonObject>

ProjectsModel::ProjectsModel(QObject *parent)
    :QAbstractListModel(parent)
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

void ProjectsModel::setName(int index, QString name)
{
     if(index >= rowCount() || index < 0)
         return;


     m_projects[index].setProjectName(name);
     dataChanged(createIndex(index,0), createIndex(index, 0));
     emit projectNameChanged(m_projects[index].id() , name);
}

QVariant ProjectsModel::getName(int index) const
{
    if(index >= rowCount() || index < 0)
        return QVariant();
    return QVariant::fromValue(m_projects[index].projectName());
}

QVariant ProjectsModel::getIsActive(int index) const
{
    if(index >= rowCount() || index < 0)
        return QVariant();
    return QVariant::fromValue(m_projects[index].isActive());
}

QVariant ProjectsModel::getIsWatcher(int index) const
{
    if(index >= rowCount() || index < 0)
        return QVariant();
    return QVariant::fromValue(m_projects[index].isWatcher());
}

QVariant ProjectsModel::getIconUrl(int index) const
{
    if(index >= rowCount() || index < 0)
        return QVariant();
    return QVariant::fromValue(m_projects[index].iconUrl());
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

void ProjectsModel::onReadProjectsInfo(const QJsonArray& projectsInfo)
{
    std::vector<ProjectInfo> projects;
    for(auto infoJson : projectsInfo)
    {
        QString prName = infoJson["name"].toString();
        bool isActive = infoJson["is_active"].toInt();
        bool isWatcher = infoJson["is_owner_watcher"].toInt();
        QString iconUrl = infoJson["logo_url"].toString();

        int spentTimeWeek = infoJson["spent_time_week"].toInt();
        int spentTimeMonth = infoJson["spent_time_month"].toInt();
        int spentTimeTotal = infoJson["spent_time_all"].toInt();
        int id = infoJson["id"].toInt();;

        projects.emplace_back(prName, isActive, isWatcher, std::vector<QPair<bool, QString>>(), iconUrl, Time(spentTimeWeek), Time(spentTimeMonth), Time(spentTimeTotal), id);
    }

    if(projects.size())
    {
        //update data
        beginResetModel();
        m_projects.swap(projects);
        endResetModel();
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

void ProjectsModel::addData(const ProjectInfo &info)
{
    m_projects.push_back(info);
}
