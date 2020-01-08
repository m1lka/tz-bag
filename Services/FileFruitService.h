#pragma once

#include "IService.h"

class FileFruitService: public IService
{
public:
    FileFruitService(std::string path);
    ~FileFruitService() {}
	
    virtual void Load() override;

private:
    std::string _path;

    bool checkParam(const std::string& name, const std::string& weight, const std::string& price);
};
