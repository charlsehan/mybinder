#ifndef  _MY_SERVICE_
#define	_MY_SERVICE_

#include <binder/IInterface.h>
#include <binder/Parcel.h>
#include <utils/String8.h>
#include <utils/String16.h>

#define MY_SERVICE "coder.core.MyService"

using namespace android;

//定义业务函数接口,声明DECLARE_META_INTERFACE()宏模板函数
class IMyService : public IInterface
{
    public:
        DECLARE_META_INTERFACE(MyService);
    public:
        virtual void sendInt(int32_t val) = 0;
        virtual int32_t getInt() = 0;
        virtual String8 getString() = 0;
    public:
        //业务函数的标号，用以区分是调用哪个业务,值对应的就是onTransact()、transact()
        //中的code参数,用在switch...case...判断中
        enum{
            SEND_INT = IBinder::FIRST_CALL_TRANSACTION,
            GET_INT,
            GET_STRING
        };
};

//定义Server组件
class BnMyService : public BnInterface<IMyService>
{
    public:
        virtual status_t onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags = 0);
};

#endif
