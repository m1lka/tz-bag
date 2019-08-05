#ifndef _FILEFRUITSERVICE_HPP
#define _FILEFRUITSERVICE_HPP

#include "IService.h"

class FileFruitService: public IService
{
public:
    FileFruitService(std::string path);
    ~FileFruitService() {}
	
    virtual void Load() override;

private:
    std::string _path;

    bool checkParam(std::string& name, std::string& weight, std::string& price);
};

#endif
