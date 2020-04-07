#pragma once
#include "ProjectInfo.h"
#include <memory>

class Parser{
public:

static void projectsInfoParse(const QJsonArray& projectsInfo, std::vector<std::shared_ptr<ProjectInfo>>& projectsOut);

};
