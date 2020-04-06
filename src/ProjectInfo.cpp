#include "ProjectInfo.h"
#include <QStringLiteral>
#include <QQmlEngine>

ProjectInfo::ProjectInfo()
{

}


ProjectInfo::ProjectInfo(const QString &projectName, bool isActive, bool isWatcher,
                         const std::vector<QPair<bool, QString> > &watchUsers,
                         const QString &iconUrl, const Time& timeThisWeek, const Time& timeThisMonth, const Time& timeTotal)
    : m_projectName(projectName), m_isActive(isActive), m_isWatcher(isWatcher),
      m_watchUsers(watchUsers), m_iconUrl(iconUrl),
      m_timeThisWeek(timeThisWeek), m_timeThisMonth(timeThisMonth), m_timeTotal(timeTotal)
{
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

std::vector<QPair<bool, QString> > ProjectInfo::watchUsers() const
{
    return m_watchUsers;
}

QString ProjectInfo::iconUrl() const
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

Time::Time(int hours, int minutes, int seconds)
    :m_hours(hours), m_minutes(minutes), m_seconds(seconds)
{

}

QString Time::toString()
{
    return QStringLiteral("%1/%2/%3").arg(m_hours).arg(m_minutes).arg(m_seconds);
}
