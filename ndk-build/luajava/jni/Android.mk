# Copyright (C) 2010 The Android Open Source Project
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#      http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.
#
LOCAL_PATH := $(call my-dir)
# TARGET_ARCH_ABI := all

# 第一步 导入静态库(使用预构建库)
include $(CLEAR_VARS)
LOCAL_MODULE    := lua
LOCAL_SRC_FILES := ${TARGET_ARCH_ABI}/liblua.a
#LOCAL_SRC_FILES := liblua.a
include $(PREBUILT_STATIC_LIBRARY)


# 第二个为动态库,在动态库中使用我们编译的静态库
include $(CLEAR_VARS)
LOCAL_MODULE    := luajava
LOCAL_SRC_FILES := luajava.c
LOCAL_LDLIBS := -llog
LOCAL_STATIC_LIBRARIES := lua
##As explained in the ndk doc, it is because the ndk performs a debug checking even for avoiding runtime linking error and for some motivations it doesn't find the correct references in a pre-built library.
LOCAL_ALLOW_UNDEFINED_SYMBOLS := true
include $(BUILD_SHARED_LIBRARY)

