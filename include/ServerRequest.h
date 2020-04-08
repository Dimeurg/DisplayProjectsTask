#pragma once

#include <QNetworkAccessManager>
#include <QJsonArray>
#include <QObject>

class ServerRequest : public QObject
{
    Q_OBJECT
public:
    ServerRequest(QObject * parent = nullptr);
    ~ServerRequest();

    void loginRequest(const QString& name, const QString& password);
    void readProjectInfoRequest(const QString& token);
    void changeProjectName(const QString& token, int id, const QString& name);

signals:
    void loginResultError(const QString& errorText);
    void loginResultProjects(const QJsonArray& projectsInfo);
    void loginResultToken(const QString& token);

public slots:
    void onLoginReplyFinished(QNetworkReply* reply);
    void onGetProjectsReplyFinished(QNetworkReply* reply);
    void onChangeProjectNameFinished(QNetworkReply* reply);

private:
    QNetworkAccessManager m_manager;

};

