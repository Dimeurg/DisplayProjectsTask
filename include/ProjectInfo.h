#pragma once
#include <QString>
#include <vector>
#include <QPair>

struct Time{
    Time() = default;
    Time(int hours, int minutes, int seconds);
    QString toString();

private:
    int m_hours;
    int m_minutes;
    int m_seconds;
};

class ProjectInfo{
public:
    ProjectInfo();
    ProjectInfo(const QString& projectName, bool isActive, bool isWatcher,
                const std::vector<QPair<bool, QString>>& watchUsers,
                const QString& iconUrl,const Time& timeThisWeek, const Time& timeThisMonth, const Time& timeTotal);

    QString projectName() const;
    bool isActive() const;
    bool isWatcher() const;
    std::vector<QPair<bool, QString> > watchUsers() const;
    QString iconUrl() const;

    Time timeThisWeek() const;
    Time timeThisMonth() const;
    Time timeTotal() const;

private:

    QString m_projectName;
    bool m_isActive;
    bool m_isWatcher;
    std::vector<QPair<bool, QString>> m_watchUsers;
    QString m_iconUrl;
    Time m_timeThisWeek;
    Time m_timeThisMonth;
    Time m_timeTotal;
};
