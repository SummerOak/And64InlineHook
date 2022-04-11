LOCAL_PATH := $(call my-dir)


include $(CLEAR_VARS)
LOCAL_MODULE    := hook
LOCAL_C_INCLUDES := And64InlineHook.hpp
LOCAL_SRC_FILES := And64InlineHook.cpp
include $(BUILD_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE := static-hook
LOCAL_SRC_FILES := $(LOCAL_PATH)/obj/local/$(TARGET_ARCH_ABI)/libhook.a
include $(PREBUILT_STATIC_LIBRARY)

include $(CLEAR_VARS)
LOCAL_MODULE    := summerhk
LOCAL_SRC_FILES := summerhk.c
LOCAL_STATIC_LIBRARIES := static-hook
LOCAL_LDLIBS += -llog -ldl -landroid -lz
include $(BUILD_SHARED_LIBRARY)
# include $(BUILD_EXECUTABLE)
