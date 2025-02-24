#include "../inc/ExampleService.hpp"
#include <utils/Log.h>
#include <string>

ScopedAStatus ExampleService::registerListener(const std::shared_ptr<IExampleListener>& listener)
{
    ALOGD("registerListener is called");
    if (listener == nullptr)
    {
        ALOGD("listener is null");
        return ndk::ScopedAStatus::ok();
    }
    mListener = listener;
    listener->notifyEvent(1);
    ALOGD("notify respond event when registering successfully");
    return ndk::ScopedAStatus::ok();
}

ScopedAStatus ExampleService::unregisterListener(const std::shared_ptr<IExampleListener>& listener)
{
    ALOGD("unregisterListener is called");
    if (listener == nullptr)
    {
        ALOGD("listener is null");
        return ndk::ScopedAStatus::ok();
    }

    if (listener)
    {
        listener->notifyEvent(0);
        mListener = nullptr;
    }

    ALOGD("notify respond event when unregistering successfully");
    return ndk::ScopedAStatus::ok();
}

ScopedAStatus ExampleService::readDeviceFile() 
{
    ALOGD("readDeviceFile is called");
    std::string content = mDriverHandler->readFile(pathExampleDriver);
    int value = std::stoi(content);
    if (mListener)
    {
        mListener->notifyEvent(value);
    }
    return ndk::ScopedAStatus::ok();
}

ScopedAStatus ExampleService::writeDeviceFile(const std::string& data) 
{
    ALOGD("writeDeviceFile is called");
    mDriverHandler->writeFile(pathExampleDriver, data.c_str());
    return ndk::ScopedAStatus::ok();
}
