#include "ProjectInfo.h"
#include <QAbstractListModel>
#include "ServerRequest.h"
#include <memory>

class ProjectsModel : public QAbstractListModel{
    Q_OBJECT

    Q_PROPERTY(bool isLogged READ isLogged NOTIFY loggedStateChanged)
    Q_PROPERTY(QString errorText READ errorText NOTIFY errorTextChanged)
    Q_PROPERTY(QString errorLoginText READ loginErrorText NOTIFY errorLoginTextChanged)
public:
    ProjectsModel(QObject* parent = nullptr);
    ~ProjectsModel();

    static void registerMe(const std::string& moduleName);

    int rowCount(const QModelIndex& parent = QModelIndex()) const override;
    QVariant data(const QModelIndex& index = QModelIndex(), int role = Qt::DisplayRole) const override;

    Q_INVOKABLE QVariant getProjectInfo(int index) const;
    Q_INVOKABLE void resetToken();
    Q_INVOKABLE void resetErrorMessage();

    QHash<int, QByteArray> roleNames() const override;

    QString errorText() const;
    void setErrorText(const QString& text);

    bool isLogged() const;

    QString loginErrorText() const;
    void setLoginErrorText(const QString &loginErrorText);

public slots:
    void onReadProjectsInfo(const QJsonArray& projectsInfo);
    void onProjectNameChanged(int id, const QString& name);
    void loginCheck(const QString& name, const QString& password);
    void onLogged(const QString& token);


signals:
    void errorTextChanged();
    void errorLoginTextChanged();
    void loggedStateChanged(bool isLogged);

private:
    void readProjectsInfo();
    enum ProjectRoles
    {
        ProjectNameRole = Qt::UserRole +1,
        IsActiveRole,
        IsWatcherRole,
        UsersRole,
        IconUrlRole,
        TimeThisWeekRole,
        TimeThisMonthRole,
        TimeTotalRole
    };

    std::vector<std::shared_ptr<ProjectInfo>> m_projects;
    QString m_token;
    ServerRequest m_serverRequest;
    QString m_errorText;
    QString m_loginErrorText;
    bool m_isLogged;
};
