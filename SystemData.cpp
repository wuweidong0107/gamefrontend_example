#include "SystemData.h"
#include "GameData.h"
#include <string>
#include <iostream>
#include <boost/filesystem.hpp>
#include <fstream>

namespace fs = boost::filesystem;

SystemData::SystemData(std::string name, std::string startPath, std::string extension, std::string command)
{
    mName = name;
    mStartPath = startPath;
    mSearchExtension = extension;
    mLaunchCommand == command;
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

void SystemData::launchGame(unsigned int i)
{

}

std::vector<SystemData*> SystemData::loadConfig(std::string path)
{
   std::cout << "Loading system config file \"" << path << "\"...\n";
   std::vector<SystemData*> returnVec;

    std::ifstream file(path.c_str());

    if (file.is_open()) {
        std::string line;
        std::string sysName, sysPath, sysExtension, sysCommand;
        while(file.good()) {
            std::getline(file, line);
            std::cout<<"++++++++"<<line<<"\n";
            if (line.empty())
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
std::cout<<"---"<<sysName<<"---"<<sysPath<<"---"<<sysExtension<<"---"<<sysCommand<<"\n";
                if (!sysName.empty() && !sysPath.empty() && !sysExtension.empty() && !sysCommand.empty()) {
                    returnVec.push_back(new SystemData(sysName, sysPath, sysExtension, sysCommand));
                    sysName = ""; sysPath = ""; sysExtension = "";
                } 
            } else {
                std::cerr << "Error reading config file \"" << path << "\" - no equals sign found on line \"" << line << "\"!\n";
				return returnVec;
            }
        }
    } else {
        std::cerr << "Error - could not load config file \"" << path << "\"!\n";
        return returnVec;
    }

    std::cout << "Finished loading config file - created " << returnVec.size() << " systems.\n";
	return returnVec;
}
