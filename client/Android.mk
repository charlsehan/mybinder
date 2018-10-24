LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE_TAGSS := optional
LOCAL_SRC_FILES := ../extra/IMyService.cpp \
					MyClient.cpp
LOCAL_SHARED_LIBRARIES := libcutils libutils libbinder
LOCAL_MODULE := MyClient
include $(BUILD_EXECUTABLE)
