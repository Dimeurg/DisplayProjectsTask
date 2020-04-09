#include "ServerRequest.h"

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QUrlQuery>

#include <QDebug>

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

#include "Parser.h"
#include "ProjectInfo.h"


ServerRequest::ServerRequest(QObject * parent)
    :QObject(parent)
{

}

ServerRequest::~ServerRequest()
{

}

void ServerRequest::onLoginReplyFinished()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(QObject::sender());
    QString answer = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(answer.toUtf8());
    QJsonObject jsonResult = jsonDoc.object();

    if(jsonResult.contains("first_errors"))
    {
        QString errorText;
        QJsonObject errorJson = jsonResult["first_errors"].toObject();
        for(auto iter = errorJson.begin(); iter != errorJson.end(); ++iter)
        {
            errorText += iter->toString() + "\n";
        }

        emit loginResultError(errorText);
    }

    else
    {
        if(reply->error())
        {
            emit requestError("Unknown error");
        }

        else
        {
            emit loginResultToken(jsonResult["token"].toString());
        }
    }
}

void ServerRequest::loginRequest(const QString& name, const QString& password)
{
    QNetworkRequest request(QUrl("https://api.quwi.com/v2/auth/login"));

    QUrlQuery params;
    params.addQueryItem("email", name.toUtf8());
    params.addQueryItem("password", password.toUtf8());

    QNetworkReply *reply = m_manager.post(request, params.query().toUtf8());
    QObject::connect(reply, &QNetworkReply::finished, this, &ServerRequest::onLoginReplyFinished);
    QObject::connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &ServerRequest::onError);
}

void ServerRequest::onGetProjectsReplyFinished()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(QObject::sender());

    QString answer = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(answer.toUtf8());
    QJsonObject jsonResult = jsonDoc.object();

    if(jsonResult.contains("first_errors"))
    {
        QString errorText;
        QJsonObject errorJson = jsonResult["first_errors"].toObject();
        for(auto iter = errorJson.begin(); iter != errorJson.end(); ++iter)
        {
            errorText += iter->toString() + "\n";
        }

        qDebug() << errorText;
    }

    else
    {
        if(reply->error())
        {
            emit requestError("Unknown error");
        }

        else
        {
            emit loginResultProjects(jsonResult["projects"].toArray());
        }
    }
}

void ServerRequest::readProjectInfoRequest(const QString& token)
{
    QNetworkRequest request(QUrl("https://api.quwi.com/v2/projects-manage/index"));

    request.setRawHeader("Authorization", ("Bearer " + token.toUtf8()));

    QNetworkReply *reply = m_manager.get(request);

    QObject::connect(reply, &QNetworkReply::finished, this, &ServerRequest::onGetProjectsReplyFinished);
    QObject::connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &ServerRequest::onError);
}

void ServerRequest::onChangeProjectNameFinished()
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(QObject::sender());

    QString answer = reply->readAll();
    QJsonDocument jsonDoc = QJsonDocument::fromJson(answer.toUtf8());
    QJsonObject jsonResult = jsonDoc.object();

    if(jsonResult.contains("first_errors"))
    {
        QString errorText;
        QJsonObject errorJson = jsonResult["first_errors"].toObject();
        for(auto iter = errorJson.begin(); iter != errorJson.end(); ++iter)
        {
            errorText += iter->toString() + "\n";
        }

        qDebug() << errorText;
    }
}

void ServerRequest::onError(QNetworkReply::NetworkError error)
{
    QNetworkReply* reply = qobject_cast<QNetworkReply*>(QObject::sender());
    emit requestError("Error id: " + QString::number(error) + " text: " + reply->errorString());
}

void ServerRequest::changeProjectName(const QString &token, int id, const QString &name)
{

    QNetworkRequest request(QUrl("https://api.quwi.com/v2/projects-manage/update?id=" + QString::number(id)));
    request.setRawHeader("Authorization", ("Bearer " + token.toUtf8()));

    QUrlQuery params;
    params.addQueryItem("name", name);

    QNetworkReply *reply = m_manager.post(request, params.toString().toUtf8());

    QObject::connect(reply, &QNetworkReply::finished, this, &ServerRequest::onChangeProjectNameFinished);
    QObject::connect(reply, static_cast<void (QNetworkReply::*)(QNetworkReply::NetworkError)>(&QNetworkReply::error), this, &ServerRequest::onError);
}

