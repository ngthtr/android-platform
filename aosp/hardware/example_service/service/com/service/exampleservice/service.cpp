#include <utils/Log.h>
#include <fcntl.h>     // For open()
#include <unistd.h>    // For close(), read(), write()
#include "inc/DriverHandler.hpp"
#include "inc/ExampleService.hpp"
#include <android/binder_manager.h>
#include <android/binder_process.h>

int main(void)
{
    ABinderProcess_setThreadPoolMaxThreadCount(0);
    ABinderProcess_startThreadPool();
    ALOGD("Start ExampleService completed");

    std::shared_ptr<ExampleService> mExampleService = ndk::SharedRefBase::make<ExampleService>();
    if (mExampleService)
    {
        ALOGD("Get ExampleService successfully");
        const char* instance = "com.example.api.aidl.IExampleService/default";
        binder_status_t status = AServiceManager_addService(mExampleService->asBinder().get(), instance);
        ALOGD(status == STATUS_OK ? "Add AIDL successfully, status = %d" : "Add AIDL failed, status = %d", status);
    }
    
    ABinderProcess_joinThreadPool();

    return 0;
}

