#include <binder/IServiceManager.h>
#include "../extra/IMyService.h"

int main()
{
    sp<IBinder> binder = defaultServiceManager()->getService((String16(MY_SERVICE)));
    if (binder == NULL) {
        printf("Failed to get the MyService binder object.\n");
        return -1;
    }

    sp<IMyService> service = IMyService::asInterface(binder);
    if (service == NULL) {
        printf("Failed to get the MyService service.\n");
        return -1;
    }

    String8 str1 = service->getString();
    printf("we get string value: %s \n",str1.string());

    int v1 = service->getInt();
    printf("we get int value: %d \n", v1);

    service->sendInt(2);

    String8 str2 = service->getString();
    printf("we get string value: %s\n",str2.string());

    int v2 = service->getInt();
    printf("we get int value: %d \n", v2);
}
