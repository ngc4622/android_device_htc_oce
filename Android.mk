#
# Copyright (C) 2012-2017 The Android Open Source Project
# Copyright (C) 2018 The LineageOS Project
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

# This contains the module build definitions for the hardware-specific
# components for this device.
#
# As much as possible, those components should be built unconditionally,
# with device-specific names to avoid collisions, to avoid device-specific
# bitrot and build breakages. Building a component unconditionally does
# *not* include it on all devices, so it is safe even with hardware-specific
# components.

LOCAL_PATH := $(call my-dir)

ifneq ($(filter oce,$(TARGET_DEVICE)),)
include $(call all-makefiles-under,$(LOCAL_PATH))

include $(CLEAR_VARS)

WCD_SYMLINKS := $(TARGET_OUT_VENDOR)/etc/firmware/wcd9320/
$(WCD_SYMLINKS): $(LOCAL_INSTALLED_MODULE)
	@echo "Creating wcd9320 folder structure: $@"
	@rm -rf $@/
	@mkdir -p $(dir $@)
	$(hide) ln -sf /data/vendor/misc/audio/wcd9320_anc.bin $@/wcd9320_anc.bin
	$(hide) ln -sf /data/vendor/misc/audio/wcd9320_mad_audio.bin $@/wcd9320_mad_audio.bin
	$(hide) ln -sf /data/vendor/misc/audio/wcd9320_mbhc.bin $@/wcd9320_mbhc.bin

ALL_DEFAULT_INSTALLED_MODULES += $(WCD_SYMLINKS) 

#MC_SYMLINKS := $(PRODUCT_OUT)/root/firmware/image/
#$(MC_SYMLINKS): $(LOCAL_INSTALLED_MODULE)
#	@echo "Creating mobicore folder structure $@"
#	@rm -rf $@/
#	@mkdir -p $(dir $@)
#	$(hide) ln -sf /system/etc/firmware/mc_v2.b00 $@/mc_v2.b00
#	$(hide) ln -sf /system/etc/firmware/mc_v2.b01 $@/mc_v2.b01
#	$(hide) ln -sf /system/etc/firmware/mc_v2.b02 $@/mc_v2.b02
#	$(hide) ln -sf /system/etc/firmware/mc_v2.b03 $@/mc_v2.b03
#	$(hide) ln -sf /system/etc/firmware/mc_v2.b04 $@/mc_v2.b04
#	$(hide) ln -sf /system/etc/firmware/mc_v2.b05 $@/mc_v2.b05
#	$(hide) ln -sf /system/etc/firmware/mc_v2.b06 $@/mc_v2.b06
#	$(hide) ln -sf /system/etc/firmware/mc_v2.mdt $@/mc_v2.mdt
#
#ALL_DEFAULT_INSTALLED_MODULES += $(MC_SYMLINKS)

RFS_MSM_ADSP_SYMLINKS := $(TARGET_OUT_VENDOR)/rfs/msm/adsp/
$(RFS_MSM_ADSP_SYMLINKS): $(LOCAL_INSTALLED_MODULE)
	@echo "Creating RFS MSM ADSP folder structure: $@"
	@rm -rf $@/
	@mkdir -p $(dir $@)/readonly/vendor
	$(hide) ln -sf /persist/hlos_rfs/shared $@/hlos
	$(hide) ln -sf /data/vendor/tombstones/rfs/lpass $@/ramdumps
	$(hide) ln -sf /persist/rfs/msm/adsp $@/readwrite
	$(hide) ln -sf /persist/rfs/shared $@/shared
	$(hide) ln -sf /firmware $@/readonly/firmware
	$(hide) ln -sf /vendor/firmware $@/readonly/vendor/firmware

RFS_MSM_MPSS_SYMLINKS := $(TARGET_OUT_VENDOR)/rfs/msm/mpss/
$(RFS_MSM_MPSS_SYMLINKS): $(LOCAL_INSTALLED_MODULE)
	@echo "Creating RFS MSM MPSS folder structure: $@"
	@rm -rf $@/
	@mkdir -p $(dir $@)/readonly/vendor
	$(hide) ln -sf /persist/hlos_rfs/shared $@/hlos
	$(hide) ln -sf /data/vendor/tombstones/rfs/modem $@/ramdumps
	$(hide) ln -sf /persist/rfs/msm/mpss $@/readwrite
	$(hide) ln -sf /persist/rfs/shared $@/shared
	$(hide) ln -sf /firmware $@/readonly/firmware
	$(hide) ln -sf /vendor/mbn $@/readonly/mbn
	$(hide) ln -sf /firmware/wsd $@/readonly/wsd
	$(hide) ln -sf /vendor/firmware $@/readonly/vendor/firmware

RFS_MSM_SLPI_SYMLINKS := $(TARGET_OUT_VENDOR)/rfs/msm/slpi/
$(RFS_MSM_SLPI_SYMLINKS): $(LOCAL_INSTALLED_MODULE)
	@echo "Creating RFS MSM SLPI folder structure: $@"
	@rm -rf $@/
	@mkdir -p $(dir $@)/readonly
	$(hide) ln -sf /persist/hlos_rfs/shared $@/hlos
	$(hide) ln -sf /data/vendor/tombstones/rfs/slpi $@/ramdumps
	$(hide) ln -sf /persist/rfs/msm/slpi $@/readwrite
	$(hide) ln -sf /persist/rfs/shared $@/shared
	$(hide) ln -sf /firmware $@/readonly/firmware

ALL_DEFAULT_INSTALLED_MODULES += $(RFS_MSM_ADSP_SYMLINKS) $(RFS_MSM_MPSS_SYMLINKS) $(RFS_MSM_SLPI_SYMLINKS)

endif
