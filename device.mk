#
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

# Include proprietary bits
$(call inherit-product, vendor/htc/oce/oce-vendor.mk)

# Ramdisk
PRODUCT_COPY_FILES += \
    $(LOCAL_PATH)/root/00-memory-dump:root/crashdump.d/00-memory-dump \
    $(LOCAL_PATH)/root/cwkeys:root/cwkeys \
    $(LOCAL_PATH)/root/fstab.qcom:root/fstab.qcom \
    $(LOCAL_PATH)/root/init.hosd_fusion.usb.rc:root/init.hosd_fusion.usb.rc \
    $(LOCAL_PATH)/root/init.hosd.htc_oce.rc:root/init.hosd.htc_oce.rc \
    $(LOCAL_PATH)/root/init.hosd.nanohub.rc:root/init.hosd.nanohub.rc \
    $(LOCAL_PATH)/root/init.hosd.usb.configfs.rc:root/init.hosd.usb.configfs.rc \
    $(LOCAL_PATH)/root/init.hosd.usb.rc:root/init.hosd.usb.rc \
    $(LOCAL_PATH)/root/init.htc.storage.exfat.rc:root/init.htc.storage.exfat.rc \
    $(LOCAL_PATH)/root/init.htc.storage.mocana.rc:root/init.htc.storage.mocana.rc \
    $(LOCAL_PATH)/root/init.htc.touch.rc:root/init.htc.touch.rc \
    $(LOCAL_PATH)/root/init.recovery.common.rc:root/init.recovery.common.rc \
    $(LOCAL_PATH)/root/init.recovery.hlthchrg.rc:root/init.recovery.hlthchrg.rc \
    $(LOCAL_PATH)/root/init.recovery.htc_oce.rc:root/init.recovery.htc_oce.rc \
    $(LOCAL_PATH)/root/init.recovery.service.rc:root/init.recovery.service.rc \
    $(LOCAL_PATH)/root/ueventd.htc_oce.rc:root/ueventd.htc_oce.rc
