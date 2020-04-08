#pragma once
#include <QPair>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>
#include <QObject>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "Parser.h"
#include "ProjectInfo.h"

class ServerRequest : public QObject
{
    Q_OBJECT
signals:
    void loginResultError(const QString& errorText);
    void loginResultProjects(const QJsonArray& projectsInfo);
    void loginResultToken(const QString& token);

public slots:
    void onLoginReplyFinished(QNetworkReply* reply);
    void onGetProjectsReplyFinished(QNetworkReply* reply);
    void onChangeProjectNameFinished(QNetworkReply* reply);
public:
    ServerRequest(QObject * parent = nullptr);

    ~ServerRequest();

    void loginRequest(const QString& name, const QString& password);
    void readProjectInfoRequest(const QString& token);
    void changeProjectName(const QString& token, int id, const QString& name);

};

