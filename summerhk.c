#include <stdio.h>
#include <dlfcn.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "And64InlineHook.hpp"
#include "jni.h"
#include "log.h"

#define LOG_TAG "summerhk"

static void* (*proto_fopen)(const char *path, const char *mode) = NULL;
static void* (*proto_fstatat)(int fd, const char* path, struct stat* st, int flag) = NULL;

int isFileNotExist(const char *path){
	return strstr(path, "_game_config0.py")
		|| strstr(path, "ziyuandi_shi_05_04_light.gim")
		|| strstr(path, "ziyuandi_shi_05_04_light.mesh")
		|| strstr(path, ".stb")
		|| strstr(path, ".blt")
		|| strstr(path, ".clt")
		|| strstr(path, "real3d_2/model/mianzhan/")
		|| strstr(path, "qiancao_10x10_d_39.astc")
		|| strstr(path, "real3d_2/landscape")
		|| strstr(path, "/sound/map_public/")
		|| strstr(path, "res/ui/Default/")
		|| strstr(path, "cfg_3d_sys_loading")
		|| strstr(path, "core_framework/ui/guide")
		|| strstr(path, "ziyuandi_light/tree_0_1_05_light.gim")
		|| strstr(path, "ziyuandi_light/tree_0_1_07_light.gim")
		|| strstr(path, "ziyuandi_light/tree_0_1_09_light.gim")
		|| strstr(path, "ziyuandi_light/tree_0_1_10_light.gim")
		|| strstr(path, "ziyuandi_light/tree_0_1_11_light.gim")
		|| strstr(path, "ziyuandi_light/tree_0_1_12_light.gim")
		|| strstr(path, "ui6_particles/Plist/dianji_01.plist")
		|| strstr(path, "ui/fonts/Droid.ttf")
		|| strstr(path, "_game_config0/__init__.py");
		
}

FILE * hook_fopen(const char *path, const char *mode){
	if(isFileNotExist(path)){
        // ALOGE("skip fopen: %s", path);
		return NULL;
	}

	return proto_fopen(path, mode);
}

int hook_fstatat(int fd, const char* path, struct stat* st, int flag){
	if(isFileNotExist(path)){
        // ALOGE("skip fstatat: %s", path);
		return -1;
	}
	
	return proto_fstatat(fd, path, st, flag);
}

void hook(){
    A64HookFunction(fstatat, hook_fstatat, &proto_fstatat);
    A64HookFunction(fopen, hook_fopen, &proto_fopen);
    ALOGE("hook result: proto_fstatat=%p, proto_fopen=%p", proto_fstatat, proto_fopen);
}

jint JNI_OnLoad(JavaVM* vm, void* reserved) {
    ALOGE("JNI_OnLoad");
    hook();
    return JNI_VERSION_1_4;
}

int main()
{
    puts("test");
    hook();
    ALOGE("after hook");
    puts("test");
    return 0;
}