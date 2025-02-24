#ifndef DRIVERHANDLER_H
#define DRIVERHANDLER_H
#include <string>

class DriverHandler
{
public:
    std::string readFile(std::string path_file);
    bool writeFile(std::string path_file, const char* data);
    long ioctlFile(std::string path_file, int command, int arg);
    void* mMapFile(std::string path_file);

};
#endif