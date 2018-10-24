#include <binder/IServiceManager.h>
#include <binder/IPCThreadState.h>

#include "../extra/IMyService.h"

class MyService : public BnMyService
{
    public:
        MyService(){option = 0;}
        virtual ~MyService(){}
    public:
        static void instance(){
            defaultServiceManager()->addService(String16(MY_SERVICE), new MyService());
        }

        void sendInt(int32_t val)
        {
            option = val;
        }

        int32_t getInt()
        {
            return option;
        }

        String8 getString()
        {
            if(option <= 0)
                return String8("you may not set val, or the value you set is <= 0.");
            else
                return String8("you have set the option with the value > 0.");

            return String8("this is default string value.");
        }
    private:
        int32_t option;
};

int main(int argc, char** argv)
{
    //注册MyService服务到系统中
    MyService::instance();

    //开启线程池，接收处理Client发送的进程间通信请求
    ProcessState::self()->startThreadPool();
    IPCThreadState::self()->joinThreadPool();

    return 0;
}
