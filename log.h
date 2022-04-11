#include<android/log.h>

#define LOGD(...)  __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__);
#define LOGR(...)  __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__);

#define ALOGE(...) __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__);
#define ALOGW(...) __android_log_print(ANDROID_LOG_WARN, LOG_TAG, __VA_ARGS__);
#define ALOGD(...) __android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__);

//#define LOGD(fmt...) async_safe_format_log(ANDROID_LOG_DEBUG, TAG, fmt);
