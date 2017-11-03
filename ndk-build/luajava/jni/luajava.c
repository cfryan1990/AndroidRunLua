//
// Created by chenfeng on 2017/11/2.
//

#include <jni.h>
#include <string.h>
#include <android/log.h>
#include "lauxlib.h"
#include "lua.h"
#include "lualib.h"

#define TAG "my_jni_log"

JNIEXPORT jstring JNICALL
Java_com_cfryan_luasample_LuaState_stringFromJNI(JNIEnv *env, jobject instance) {

    return (*env)->NewStringUTF(env, "hello lua!");
}

void dump(lua_State *L) {
    int n = lua_gettop(L);
    int i;

    for (i = 1; i <= n; i++) {
        int type = lua_type(L, i);
        switch (type) {
            case LUA_TNUMBER:
                __android_log_print(ANDROID_LOG_DEBUG, TAG, "%d : %g\n", i, lua_tonumber(L, i));
                break;

            case LUA_TSTRING:
                __android_log_print(ANDROID_LOG_DEBUG, TAG, "%d : %s\n", i, lua_tostring(L, i));
                break;

            case LUA_TBOOLEAN:
                __android_log_print(ANDROID_LOG_DEBUG, TAG, "%d : %s\n", i,
                                    lua_toboolean(L, i) ? "true" : "false");
                break;

            case LUA_TFUNCTION:
                __android_log_print(ANDROID_LOG_DEBUG, TAG, "%d : function\n", i);
                break;

            default:
                __android_log_print(ANDROID_LOG_DEBUG, TAG, "%d : %d\n", i, type);
                break;
        }
    }
}

JNIEXPORT void JNICALL
Java_com_cfryan_luasample_LuaState_doFile(JNIEnv *env, jobject instance, jstring path_) {
    const char *path = (*env)->GetStringUTFChars(env, path_, 0);

    const char *filePath = (*env)->GetStringUTFChars(env, path_, NULL);
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "Java_lua_1java_Main_doFile: %s\n", filePath);

    lua_State *L = luaL_newstate();
    luaL_openlibs(L);
//    luaL_dofile(L, filePath);

    luaL_dostring(L, "function power(a,n) return a^n end");

    lua_getglobal(L, "power");
    lua_pushinteger(L, 2);
    lua_pushinteger(L, 1000);
    lua_call(L, 2, 1);
    dump(L);
    int res = lua_tonumber(L, -1);  // 取出栈顶结果
    __android_log_print(ANDROID_LOG_DEBUG, TAG, "power:%d", res);

    lua_close(L);
}


JNIEXPORT jlong JNICALL
Java_com_cfryan_luasample_LuaState__1newState(JNIEnv *env, jobject instance) {
    lua_State *L = luaL_newstate();
    return L;
}

JNIEXPORT void JNICALL
Java_com_cfryan_luasample_LuaState__1openLibs(JNIEnv *env, jobject instance, jlong j) {
    luaL_openlibs(j);
}

JNIEXPORT void JNICALL
Java_com_cfryan_luasample_LuaState__1doString(JNIEnv *env, jobject instance, jlong j, jstring s_) {
    const char *s = (*env)->GetStringUTFChars(env, s_, 0);

    luaL_dostring(j, s);

    (*env)->ReleaseStringUTFChars(env, s_, s);
}

JNIEXPORT void JNICALL
Java_com_cfryan_luasample_LuaState__1getGlobal(JNIEnv *env, jobject instance, jlong j,
                                               jstring name_) {
    const char *name = (*env)->GetStringUTFChars(env, name_, 0);

    lua_getglobal(j, name);

    (*env)->ReleaseStringUTFChars(env, name_, name);
}

JNIEXPORT void JNICALL
Java_com_cfryan_luasample_LuaState__1pushInteger(JNIEnv *env, jobject instance, jlong j, jint i) {

    lua_pushinteger(j, i);

}

JNIEXPORT void JNICALL
Java_com_cfryan_luasample_LuaState__1call(JNIEnv *env, jobject instance, jlong j, jint i, jint k) {

    lua_call(j, i, k);

}

JNIEXPORT jint JNICALL
Java_com_cfryan_luasample_LuaState__1toNumber(JNIEnv *env, jobject instance, jlong j, jint i) {

    return lua_tonumber(j, i);

}

JNIEXPORT void JNICALL
Java_com_cfryan_luasample_LuaState__1close(JNIEnv *env, jobject instance, jlong j) {

    lua_close(j);

}
