#pragma once
#include <QString>
#include <vector>
#include <QPair>
#include <QObject>
#include <QUrl>

struct Time{
    Time() = default;
    Time(int hours, int minutes, int seconds);
    Time(int timeInSeconds);
    QString toString();

private:
    int m_hours;
    int m_minutes;
    int m_seconds;
};

class ProjectInfo : public QObject{
    Q_OBJECT

    Q_PROPERTY(QString projectName READ projectName WRITE setProjectName NOTIFY projectNameChanged)
    Q_PROPERTY(bool isActive READ isActive)
    Q_PROPERTY(bool isWatcher READ isWatcher)
    Q_PROPERTY(QUrl iconUrl READ iconUrl)
    Q_PROPERTY(int id READ id)

public:
    explicit ProjectInfo(QObject * parent = nullptr);
    ProjectInfo(const QString& projectName, bool isActive, bool isWatcher,
                const std::vector<QPair<bool, QString>>& watchUsers,
                const QUrl& iconUrl,const Time& timeThisWeek, const Time& timeThisMonth, const Time& timeTotal,
                int id, QObject * parent = nullptr);

    static void registerMe(const std::string& moduleName);

    QString projectName() const;
    bool isActive() const;
    bool isWatcher() const;
    std::vector<QPair<bool, QString> > watchUsers() const;
    QUrl iconUrl() const;

    Time timeThisWeek() const;
    Time timeThisMonth() const;
    Time timeTotal() const;

    void setProjectName(const QString &projectName);
    int id() const;

signals:
    void projectNameChanged();

private:

    QString m_projectName;
    bool m_isActive;
    bool m_isWatcher;
    std::vector<QPair<bool, QString>> m_watchUsers;
    QUrl m_iconUrl;
    Time m_timeThisWeek;
    Time m_timeThisMonth;
    Time m_timeTotal;
    int m_id;
};

Q_DECLARE_METATYPE(const ProjectInfo*)
