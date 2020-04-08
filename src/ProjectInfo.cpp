#include "ProjectInfo.h"
#include <QStringLiteral>
#include <QQmlEngine>

ProjectInfo::ProjectInfo(QObject * parent)
    :QObject(parent)
{

}


ProjectInfo::ProjectInfo(const QString &projectName, bool isActive, bool isWatcher,
                         const QString &users, const QUrl &iconUrl, const Time& timeThisWeek, const Time& timeThisMonth,
                         const Time& timeTotal, int id, QObject * parent)
    : QObject(parent),
      m_projectName(projectName), m_isActive(isActive), m_isWatcher(isWatcher),
      m_users(users), m_iconUrl(iconUrl),
      m_timeThisWeek(timeThisWeek), m_timeThisMonth(timeThisMonth), m_timeTotal(timeTotal), m_id(id)
{

}

void ProjectInfo::registerMe(const std::string &moduleName)
{
    qmlRegisterType<ProjectInfo>(moduleName.c_str(), 1, 0, "ProjectInfo");
}

QString ProjectInfo::projectName() const
{
    return m_projectName;
}

bool ProjectInfo::isActive() const
{
    return m_isActive;
}

bool ProjectInfo::isWatcher() const
{
    return m_isWatcher;
}

QUrl ProjectInfo::iconUrl() const
{
    return m_iconUrl;
}

Time ProjectInfo::timeThisWeek() const
{
    return m_timeThisWeek;
}

Time ProjectInfo::timeThisMonth() const
{
    return m_timeThisMonth;
}

Time ProjectInfo::timeTotal() const
{
    return m_timeTotal;
}

void ProjectInfo::setProjectName(const QString &projectName)
{
    if(projectName != m_projectName)
    {
        m_projectName = projectName;
        emit projectNameChanged(m_id, m_projectName);
    }
}

int ProjectInfo::id() const
{
    return m_id;
}

QString ProjectInfo::users() const
{
    return m_users;
}

Time::Time(int hours, int minutes, int seconds)
    :m_hours(hours), m_minutes(minutes), m_seconds(seconds)
{

}

Time::Time(int timeInSeconds)
{
    const int SecondsInHour = 3600;
    const int SecondsInMinute = 3600;

    const int hours = timeInSeconds / SecondsInHour;
    timeInSeconds -= hours * SecondsInHour;

    const int minutes = timeInSeconds / SecondsInMinute;
    const int seconds = timeInSeconds - minutes * SecondsInMinute;

    m_hours = hours;
    m_minutes = minutes;
    m_seconds = seconds;
}

QString Time::toString()
{
    return QStringLiteral("%1/%2/%3").arg(m_hours).arg(m_minutes).arg(m_seconds);
}
