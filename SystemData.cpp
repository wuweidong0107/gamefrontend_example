#include "SystemData.h"
#include "GameData.h"
#include <string>
#include <iostream>
#include <boost/filesystem.hpp>
#include <fstream>
#include <stdlib.h>

std::vector<SystemData*> SystemData::sSystemVector;

namespace fs = boost::filesystem;

SystemData::SystemData(std::string name, std::string startPath, std::string extension, std::string command)
{
    mName = name;
    mStartPath = startPath;
    mSearchExtension = extension;
    mLaunchCommand = command;
    buildGameList();
}

SystemData::~SystemData()
{
    for (unsigned int i=0; i<mGameVector.size(); i++) {
        delete mGameVector.at(i);
    }
    mGameVector.clear();
}

unsigned int SystemData::getGameCount()
{
    return mGameVector.size();
}

GameData* SystemData::getGame(unsigned int i)
{
    return mGameVector.at(i);
}

std::string SystemData::getName()
{
    return mName;
}

void SystemData::buildGameList()
{
    std::cout << "System " << mName << " building game list...\n";

    if (!fs::is_directory(mStartPath)) {
        std::cout << "Error - system \"" << mName << "\"'s start path does not exist!\n";
		return;
    }
    
    for(fs::recursive_directory_iterator end, dir(mStartPath); dir != end; ++dir) {
        std::cout << "File found" << *dir << "\n";
        fs::path path = (*dir).path();

        if (fs::is_directory(path))
            continue;
        
        std::string name = path.stem().string();
        std::string extension = path.extension().string();

        std::cout << "detected name as \"" << name << "\", extension as \"" << extension << "\"\n";

        if (extension == mSearchExtension) {
            mGameVector.push_back(new GameData(this, path.string(), name));
        }

        std::cout << "...done! Found " << mGameVector.size() << "games.\n";
    }
}

std::string strreplace(std::string& str, std:: string replace, std::string with)
{
    size_t pos = str.find(replace);
    return str.replace(pos, replace.length(), with.c_str(), with.length());
}

void SystemData::launchGame(unsigned int i)
{
    std::string command = mLaunchCommand;
    GameData* game = mGameVector.at(i);

    command = strreplace(command, "%ROM%", game->getValidPath());
    std::cout << "	" << command << "\n";
    system(command.c_str());
}

void SystemData::loadConfig(std::string path)
{
    std::cout << "Loading system config file \"" << path << "\"...\n";
    deleteSystems();
    std::ifstream file(path.c_str());

    if (file.is_open()) {
        std::string line;
        std::string sysName, sysPath, sysExtension, sysCommand;
        while(file.good()) {
            std::getline(file, line);
            if (line.empty() || line[0] == *"#")
                continue;
            
            bool lineValid = false;
            std::string varName, varValue;
            for (unsigned int i=0; i<line.length(); i++) {
                if (line[i] == *"=") {
                    lineValid = true;
                    varName = line.substr(0, i);
                    varValue = line.substr(i+1, line.length()-1);
                    std::cout << "	" << varName << " = " << varValue << "\n";
                    break;
                }
            }

            if (lineValid) {
                if (varName == "NAME")
                    sysName = varValue;
                else if (varName == "PATH")
                    sysPath = varValue;
                else if (varName == "EXTENSION")
                    sysExtension = varValue;
                else if (varName == "COMMAND")
                    sysCommand = varValue;
                else
                    std::cerr << "Error reading config file - unknown variable name \"" << varName << "\"!\n";
                if (!sysName.empty() && !sysPath.empty() && !sysExtension.empty() && !sysCommand.empty()) {
                    sSystemVector.push_back(new SystemData(sysName, sysPath, sysExtension, sysCommand));
                    sysName = ""; sysPath = ""; sysExtension = ""; sysCommand = "";
                } 
            } else {
                std::cerr << "Error reading config file \"" << path << "\" - no equals sign found on line \"" << line << "\"!\n";
            }
        }
    } else {
        std::cerr << "Error - could not load config file \"" << path << "\"!\n";
        return;
    }

    std::cout << "Finished loading config file - created " << sSystemVector.size() << " systems.\n";
	return;
}

void SystemData::deleteSystems()
{
    for (unsigned int i=0; i<sSystemVector.size(); i++) {
        delete sSystemVector.at(i);
    }
    sSystemVector.clear();
}