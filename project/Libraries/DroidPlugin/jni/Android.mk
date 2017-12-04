# Copyright (C) 2009 The Android Open Source Project
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
MAIN_LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE    := gamer

LOCAL_CFLAGS := -Wno-error=format-security -fpermissive -DLOG_TAG=\"Gamer\"
LOCAL_CFLAGS += -fno-rtti -fno-exceptions

LOCAL_C_INCLUDES += $(MAIN_LOCAL_PATH)
LOCAL_C_INCLUDES += $(MAIN_LOCAL_PATH)/gamer

LOCAL_SRC_FILES := gamer/GamerJni.cpp \
                   gamer/IOUniformer.cpp \
                   gamer/SymbolFinder.cpp

LOCAL_LDLIBS := -llog -latomic
LOCAL_STATIC_LIBRARIES := hookzz fb

include $(BUILD_SHARED_LIBRARY)
include $(MAIN_LOCAL_PATH)/HookZz/Android.mk
include $(MAIN_LOCAL_PATH)/fb/Android.mk
