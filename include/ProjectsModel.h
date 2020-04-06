#include "ProjectInfo.h"
#include <QAbstractListModel>

class ProjectsModel : public QAbstractListModel{
    Q_OBJECT

    Q_PROPERTY(QString token READ token WRITE setToken NOTIFY tokenChanged)
public:
    ProjectsModel(QObject* parent = nullptr);

    static void registerMe(const std::string& moduleName);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index = QModelIndex(), int role = Qt::DisplayRole) const override;

    Q_INVOKABLE void setName(int index, QString name);

    Q_INVOKABLE QVariant getName(int index) const;
    Q_INVOKABLE QVariant getIsActive(int index) const;
    Q_INVOKABLE QVariant getIsWatcher(int index) const;
    Q_INVOKABLE QVariant getIconUrl(int index) const;

    QHash<int, QByteArray> roleNames() const override;

    QString token() const;
    void setToken(const QString &token);

    Q_INVOKABLE void addData(const ProjectInfo& info);

public slots:
    void onReadProjectsInfo(const QJsonArray& projectsInfo);

signals:
    void tokenChanged();
    void projectNameChanged(int id, QString name);

private:
    enum ProjectRoles{

        ProjectNameRole = Qt::UserRole +1,
        IsActiveRole,
        IsWatcherRole,
        WatchUsersRole,
        IconUrlRole,
        TimeThisWeekRole,
        TimeThisMonthRole,
        TimeTotalRole
    };

    std::vector<ProjectInfo> m_projects;
    QString m_token;
};
