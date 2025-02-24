#ifndef EXAMPLESERVICE_H
#define EXAMPLESERVICE_H
#include "aidl/com/example/api/aidl/BnExampleService.h"
#include "DriverHandler.hpp"

using aidl::com::example::api::aidl::BnExampleService;
using aidl::com::example::api::aidl::IExampleListener;
using ndk::ScopedAStatus;

class ExampleService : public BnExampleService
{
private:
    std::shared_ptr<DriverHandler> mDriverHandler = std::make_shared<DriverHandler>();
    std::string pathExampleDriver = "/dev/example_driver"; 
    std::shared_ptr<IExampleListener> mListener;
public:
    ScopedAStatus registerListener(const std::shared_ptr<IExampleListener>& listener) override;
    ScopedAStatus unregisterListener(const std::shared_ptr<IExampleListener>& listener) override;
    ScopedAStatus readDeviceFile() override;
    ScopedAStatus writeDeviceFile(const std::string& data) override;
};


#endif
