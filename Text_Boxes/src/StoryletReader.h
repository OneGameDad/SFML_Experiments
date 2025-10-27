#pragma once

#include <string>
#include <map>
#include <fstream>
#include <sstream>
#include <exception>
#include "ResourceManager.h"

class StoryletReader
{
private:
    std::map<std::string, std::string> storylets;
    bool    isFileLoaded = false;
    StoryletReader() = default;
    ~StoryletReader() = default;

    void loadFile(const std::string& filename)
    {
        std::ifstream file(filename);
        if (!file.is_open())
            throw std::runtime_error("Could not open file: " + filename);
        
        std::string line;
        while (std::getline(file, line))
        {
            if (line.empty())
                continue;
            
                std::istringstream ss(line);
                std::string key;
                std::string value;
                
                if (std::getline(ss, key, '\t') && std::getline(ss, value))
                {
                    storylets[key] = value;
                }
                else
                    throw std::runtime_error("Invalid line format (expected: key\\tvalue): " + line);
        }
        isFileLoaded = true;
    }

public:
    static StoryletReader& getInstance()
    {
        static StoryletReader instance;
        if (!instance.isFileLoaded)
        {
            instance.loadFile(ResourceManager::getFilePath("storylets.txt"));
        }
        return (instance);
    }

    StoryletReader(const StoryletReader& copy) = delete;
    StoryletReader& operator=(const StoryletReader& copy) = delete;

    const std::map<std::string, std::string>& getStorylets() const { return (storylets); }

    std::string getValue(const std::string& key) const
    {
        auto it = storylets.find(key);
        if (it != storylets.end())
            return (it->second);
        else
            throw std::out_of_range("Key not found: " + key);
    }
};