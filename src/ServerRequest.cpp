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

void ServerRequest::onLoginReplyFinished(QNetworkReply* reply)
{
    if (reply->error())
    {
        auto test = reply->errorString();
        emit loginResultError(reply->errorString());
    }

    else
    {
       QString answer = reply->readAll();
       QJsonDocument jsonDoc = QJsonDocument::fromJson(answer.toUtf8());
       QJsonObject jsonResult = jsonDoc.object();

       if(jsonResult.contains("first_errors"))
       {
           QString errorText;
           QJsonObject errorJson = jsonResult["first_errors"].toObject();
           for(auto iter = errorJson.begin(); iter != errorJson.end(); ++iter)
           {
               QString a = iter->toString();
               errorText += iter->toString() + "\n";
           }

           emit loginResultError(errorText);
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

    QObject::connect(reply, &QNetworkReply::readyRead,
                     [reply, this]()
    {
        onLoginReplyFinished(reply);
    });
}

void ServerRequest::onGetProjectsReplyFinished(QNetworkReply* reply)
{
    if (reply->error())
    {
        qDebug()<< reply->errorString();
    }

    else
    {
       QString answer = reply->readAll();
       QJsonDocument jsonDoc = QJsonDocument::fromJson(answer.toUtf8());
       QJsonObject jsonResult = jsonDoc.object();

       if(jsonResult.contains("first_errors"))
       {
           QString errorText;
           QJsonObject errorJson = jsonResult["first_errors"].toObject();
           for(auto iter = errorJson.begin(); iter != errorJson.end(); ++iter)
           {
               QString a = iter->toString();
               errorText += iter->toString() + "\n";
           }

           qDebug() << errorText;
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

    QObject::connect(reply, &QNetworkReply::readyRead,
                     [reply, this]()
    {
        onGetProjectsReplyFinished(reply);
    });
}

void ServerRequest::onChangeProjectNameFinished(QNetworkReply *reply)
{
    if (reply->error())
    {
        qDebug()<< reply->errorString();
    }

    else
    {
       QString answer = reply->readAll();
       QJsonDocument jsonDoc = QJsonDocument::fromJson(answer.toUtf8());
       QJsonObject jsonResult = jsonDoc.object();

       if(jsonResult.contains("first_errors"))
       {
           QString errorText;
           QJsonObject errorJson = jsonResult["first_errors"].toObject();
           for(auto iter = errorJson.begin(); iter != errorJson.end(); ++iter)
           {
               QString a = iter->toString();
               errorText += iter->toString() + "\n";
           }

           qDebug() << errorText;
       }
    }
}

void ServerRequest::changeProjectName(const QString &token, int id, const QString &name)
{

    QNetworkRequest request(QUrl("https://api.quwi.com/v2/projects-manage/update?id=" + QString::number(id)));
    request.setRawHeader("Authorization", ("Bearer " + token.toUtf8()));

    QUrlQuery params;
    params.addQueryItem("name", name);

    QNetworkReply *reply = m_manager.post(request, params.toString().toUtf8());

    QObject::connect(reply, &QNetworkReply::readyRead,
                     [reply, this]()
    {
        onChangeProjectNameFinished(reply);
    });
}

