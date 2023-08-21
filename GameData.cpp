#include "GameData.h"

GameData::GameData(SystemData* system, std::string path, std::string name)
{
    mSystem = system;
    mPath = path;
    mName = name;   
}

std::string GameData::getName()
{
    return mName;
}

std::string GameData::getValidPath()
{
    std::string path = mPath;
    for (unsigned int i=0; i<path.length(); i++) {
        if (path[i] == *" ") {
            path.insert(i, "\\");
            i++;
        }
    }
    return path;
}