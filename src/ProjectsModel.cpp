#include "ProjectsModel.h"
#include "Parser.h"
#include <QQmlEngine>
#include <QPointer>

ProjectsModel::ProjectsModel(QObject *parent)
    :QAbstractListModel(parent), m_isLogged(false)
{
    connect(&m_serverRequest, &ServerRequest::loginResultError, this, &ProjectsModel::setLoginErrorText);
    connect(&m_serverRequest, &ServerRequest::requestError, this, &ProjectsModel::setErrorText);
    connect(&m_serverRequest, &ServerRequest::loginResultToken, this, &ProjectsModel::onLogged);
    connect(&m_serverRequest, &ServerRequest::loginResultProjects, this, &ProjectsModel::onReadProjectsInfo);
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

void ProjectsModel::onProjectNameChanged(int id, const QString& name)
{
    m_serverRequest.changeProjectName(m_token, id, name);
    dataChanged(createIndex(0, 0), createIndex(m_projects.size(), 0));
}

void ProjectsModel::loginCheck(const QString& name, const QString& password)
{
    m_serverRequest.loginRequest(name, password);
}

void ProjectsModel::onLogged(const QString& token)
{
    if(m_token != token)
    {
        m_token = token;
        m_serverRequest.readProjectInfoRequest(m_token);
    }

    if(m_token != "")
    {
        m_isLogged = true;
        emit loggedStateChanged(m_isLogged);
    }

    else
    {
        m_loginErrorText = "bad token";
        emit errorLoginTextChanged();
    }
}

bool ProjectsModel::isLogged() const
{
    return m_isLogged;
}

QVariant ProjectsModel::getProjectInfo(int index) const
{
    if(index >= rowCount() || index < 0)
        return QVariant();

    return QVariant::fromValue(m_projects[index].get());
}

void ProjectsModel::resetToken()
{
    m_token = "";
    m_isLogged = false;
    emit loggedStateChanged(m_isLogged);
}

void ProjectsModel::resetErrorMessage()
{
    m_errorText = "";
    m_loginErrorText = "";
    emit errorTextChanged();
    emit errorLoginTextChanged();
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

void ProjectsModel::readProjectsInfo()
{

}

void ProjectsModel::setLoginErrorText(const QString &loginErrorText)
{
    m_loginErrorText = loginErrorText;
    emit errorLoginTextChanged();
}

QString ProjectsModel::loginErrorText() const
{
    return m_loginErrorText;
}

QString ProjectsModel::errorText() const
{
    return m_errorText;
}

void ProjectsModel::setErrorText(const QString &text)
{
    m_errorText = text;
    emit errorTextChanged();
}

