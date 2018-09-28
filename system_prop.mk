# Bluetooth properties
PRODUCT_PROPERTY_OVERRIDES += \
     qcom.bluetooth.soc=rome \
     ro.bluetooth.wipower=true \
     ro.bluetooth.emb_wp_mode=true \
     ro.bt.bdaddr_path=/sys/module/htc_bdaddress/parameters/bdaddress \
     bt.max.hfpclient.connections=1

# TODO: maybe we can abandon the last one

# CNE
PRODUCT_PROPERTY_OVERRIDES += \
    persist.cne.feature=1 \
    persist.cne.rat.wlan.chip.oem=nqc

# Dalvik configuration
PRODUCT_PROPERTY_OVERRIDES += \
    dalvik.vm.heapsize=36m  \
    dalvik.vm.heapgrowthlimit=256m \
    dalvik.vm.heapstartsize=8m \
    dalvik.vm.heapsize=512m \
    dalvik.vm.heaptargetutilization=0.75 \
    dalvik.vm.heapminfree=2m \
    dalvik.vm.heapmaxfree=8m

# Data module
PRODUCT_PROPERTY_OVERRIDES += \
    ro.use_data_netmgrd=true \
    persist.data.netmgrd.qos.enable=true \
    persist.data.mode=concurrent \
    persist.net.doxlat=false

# Display
PRODUCT_PROPERTY_OVERRIDES += \
    ro.sf.lcd_density=640 \
    hw.backlight.sre.threshold=13

# Media
PRODUCT_PROPERTY_OVERRIDES += \
    media.settings.xml=/vendor/etc/media_profiles_vendor.xml \
    vendor.vidc.enc.disable.pq=true \
    vidc.enc.dcvs.extra-buff-count=2

# OpenGLES
PRODUCT_PROPERTY_OVERRIDES += \
    ro.opengles.version=196610

# RIL
PRODUCT_PROPERTY_OVERRIDES += \
    ro.ril.enable.dtm=0 \
    ro.ril.show.all.plmn=1 \
    ro.ril.esm.blacklist=22601,26806,26801,21403,42502,25007,25054,25027 \
    ro.ril.hsxpa=4 \
    ro.ril.hsdpa.category=24 \
    ro.ril.hsupa.category=6 \
    ro.ril.disable.cpc=0 \
    ro.cw.base.version=O80 \
    persist.radio.NETWORK_SWITCH=2 \
    ro.com.android.dataroaming=false \
    rild.libpath=/vendor/lib64/libril-qc-qmi-1.so \
    telephony.lteOnCdmaDevice=1 \
    ril.subscription.types=NV,RUIM \
    DEVICE_PROVISIONED=1

# TODO: maybe we can abandon the last two props

# Set first API
PRODUCT_PROPERTY_OVERRIDES += \
    ro.product.first_api_level=25

# Vendor security patch level
PRODUCT_PROPERTY_OVERRIDES += \
    ro.lineage.build.vendor_security_patch=2018-02-01

# Wifidisplay
PRODUCT_PROPERTY_OVERRIDES += \
    persist.debug.wfd.enable=1

# For device bringup
PRODUCT_SYSTEM_DEFAULT_PROPERTIES += \
    ro.secure=0 \
    ro.adb.secure=0 \
    ro.debuggable=1 \
    persist.service.adb.enable=1 \
    persist.sys.usb.config=adb


# TODO: some properties are missing!

# TODO: unknown:
PRODUCT_PROPERTY_OVERRIDES += \
    persist.demo.hdmirotationlock=false \
    sdm.debug.disable_skip_validate=1 \
    ro.vendor.at_library=libqti-at.so \
    sys.games.gt.prof=1
