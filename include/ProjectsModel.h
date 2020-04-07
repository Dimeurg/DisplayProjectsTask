#include "ProjectInfo.h"
#include <QAbstractListModel>
#include <memory>

class ProjectsModel : public QAbstractListModel{
    Q_OBJECT

    Q_PROPERTY(QString token READ token WRITE setToken NOTIFY tokenChanged)
public:
    ProjectsModel(QObject* parent = nullptr);
    ~ProjectsModel();

    static void registerMe(const std::string& moduleName);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index = QModelIndex(), int role = Qt::DisplayRole) const override;

    Q_INVOKABLE QVariant getProjectInfo(int index) const;

    QHash<int, QByteArray> roleNames() const override;

    QString token() const;
    void setToken(const QString &token);

public slots:
    void onReadProjectsInfo(const QJsonArray& projectsInfo);
    void onProjectNameChanged();

signals:
    void tokenChanged();

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

    std::vector<std::shared_ptr<ProjectInfo>> m_projects;
    QString m_token;
};
