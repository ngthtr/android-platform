#include "../inc/DriverHandler.hpp"
#include <utils/Log.h>
#include <fcntl.h>     // For open()
#include <unistd.h>    // For close(), read(), write()
#include <string>
#include <sys/mman.h>
#include <sys/stat.h>

std::string DriverHandler::readFile(std::string path_file)
{
    const char* path_file_chr = path_file.c_str();
    int fd = open(path_file_chr, O_RDONLY);
    if (fd < 0)
    {
        ALOGD("Open file %s failed", path_file_chr);
        return "";
    }
    ALOGD("Open file %s successfully", path_file_chr);

    char content[256];
    ssize_t readBytes = read(fd, content, sizeof(content) - 1);
    ALOGD(readBytes < 0 ? "Read file %s failed" : "Read file %s successfully", path_file_chr);

    close(fd);
    
    std::string content_str(content);
    return content_str;
}

bool DriverHandler::writeFile(std::string path_file, const char* data)
{
    const char* path_file_chr = path_file.c_str();
    int fd = open(path_file_chr, O_WRONLY);
    if (fd < 0)
    {
        ALOGD("Open file %s failed", path_file_chr);
        return false;
    }
    ALOGD("Open file %s successfully", path_file_chr);

    ssize_t writeBytes = write(fd, data, strlen(data));
    ALOGD(writeBytes < 0 ? "Write file %s failed, data = %s" : "Write file %s successfully, data = %s", path_file_chr, data);

    close(fd);
    
    return true;
}

long DriverHandler::ioctlFile(std::string path_file, int command, int arg)
{
    const char* path_file_chr = path_file.c_str();
    int fd = open(path_file_chr, O_RDWR);
    if (fd < 0)
    {
        ALOGD("Open file %s failed", path_file_chr);
        return -1;
    }
    ALOGD("Open file %s successfully", path_file_chr);

    long result = ioctl(fd, command, &arg);
    ALOGD(result < 0 ? "Ioctl file %s failed" : "Ioctl file %s successfully", path_file_chr);

    close(fd);

    return result;
}

void* DriverHandler::mMapFile(std::string path_file)
{
    const char* path_file_chr = path_file.c_str();
    int fd = open(path_file_chr, O_RDWR);
    if (fd < 0)
    {
        ALOGD("Open file %s failed", path_file_chr);
        return nullptr;
    }
    ALOGD("Open file %s successfully", path_file_chr);

    struct stat file_info;
    if (fstat(fd, &file_info) == -1) {
        close(fd);
        return nullptr;
    }
    void* mmaped_memory = mmap(nullptr, file_info.st_size, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
    if (mmaped_memory == MAP_FAILED) {
        ALOGD("Mmap memory to file %s failed", path_file_chr);
        return nullptr;
    }

    // Set data to shared memory
    const char* src = "Hello world!";
    memcpy(mmaped_memory, src, strlen(src) + 1);

    ALOGD("Mmap memory to file %s successfully", path_file_chr);

    close(fd);

    return nullptr;
}
