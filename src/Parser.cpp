#include "Parser.h"

#include <QJsonArray>
#include <QJsonObject>
#include <QStringLiteral>

void Parser::projectsInfoParse(const QJsonArray& projectsInfo, std::vector<std::shared_ptr<ProjectInfo>>& projectsOutput)
{
   std::vector<std::shared_ptr<ProjectInfo>> projects;
    for(auto infoJson : projectsInfo)
    {
        QString prName = infoJson["name"].toString();
        bool isActive = infoJson["is_active"].toInt();
        bool isWatcher = infoJson["is_owner_watcher"].toInt();
        QUrl iconUrl = infoJson["logo_url"].toString();

        int spentTimeWeek = infoJson["spent_time_week"].toInt();
        int spentTimeMonth = infoJson["spent_time_month"].toInt();
        int spentTimeTotal = infoJson["spent_time_all"].toInt();
        int id = infoJson["id"].toInt();

        QString users;
        int index = 0;
        const QJsonArray& usersJson = infoJson["users"].toArray();
        for(auto user : usersJson)
        {
            users += QStringLiteral("user%1: ").arg(index++) + user["name"].toString();
        }

        projects.emplace_back(new ProjectInfo(prName, isActive, isWatcher, users, iconUrl, Time(spentTimeWeek), Time(spentTimeMonth), Time(spentTimeTotal), id));
    }

    projectsOutput.swap(projects);
}
