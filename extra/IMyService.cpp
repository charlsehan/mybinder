#include <binder/IPCThreadState.h>
#include <binder/Parcel.h>
#include "IMyService.h"

class BpMyService : public BpInterface<IMyService>
{
    public:
        BpMyService(const sp<IBinder>& impl) : BpInterface<IMyService>(impl){}
    public:
        void sendInt(int32_t val){
            Parcel data, reply;
            data.writeInterfaceToken(IMyService::getInterfaceDescriptor());
            data.writeInt32(val);

            remote()->transact(SEND_INT, data, &reply);
            int32_t excode = reply.readExceptionCode();
        }

        int32_t getInt(){
            Parcel data, reply;
            data.writeInterfaceToken(IMyService::getInterfaceDescriptor());

            remote()->transact(GET_INT, data, &reply);
            int32_t excode = reply.readExceptionCode();
            int32_t res = reply.readInt32();
            return res;
        }

        String8 getString(){
            Parcel data, reply;
            data.writeInterfaceToken(IMyService::getInterfaceDescriptor());

            remote()->transact(GET_STRING, data, &reply);
            int32_t excode = reply.readExceptionCode();
            String8 res = reply.readString8();
            return res;
        }
};

//实现IMPLEMENT_META_INTERFACE()宏模板函数
IMPLEMENT_META_INTERFACE(MyService, MY_SERVICE);

status_t BnMyService::onTransact(uint32_t code, const Parcel& data, Parcel* reply, uint32_t flags)
{
    printf("onTransact code=%d \n", code);
    switch(code){
        case SEND_INT:
            {
                CHECK_INTERFACE(IMyService, data, reply);
                int32_t val = data.readInt32();//去除传入的参数，调用服务类的函数
                sendInt(val);

                return NO_ERROR;
            }
            break;
        case GET_INT:
            {
                CHECK_INTERFACE(IMyService, data, reply);
                int32_t res = getInt();//调用服务类的函数
                reply->writeNoException();
                reply->writeInt32(res);//将结果存入reply,BpMyService端可以读出该结果

                return NO_ERROR;
            }
            break;
        case GET_STRING:
            {
                CHECK_INTERFACE(IMyService, data, reply);
                String8 res = getString();//调用服务类的函数
                printf("getString() res=%s \n", res);
                reply->writeNoException();
                reply->writeString8(res);//将结果存入reply,BpMyService端可以读出该结果

                return NO_ERROR;
            }
            break;
        default:
            return BBinder::onTransact(code, data, reply, flags);
    }
};
