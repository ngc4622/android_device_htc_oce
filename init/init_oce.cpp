/*
   Copyright (c) 2013, The Linux Foundation. All rights reserved.
   Copyright (c) 2018 The LineageOS Project

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are
   met:
    * Redistributions of source code must retain the above copyright
      notice, this list of conditions and the following disclaimer.
    * Redistributions in binary form must reproduce the above
      copyright notice, this list of conditions and the following
      disclaimer in the documentation and/or other materials provided
      with the distribution.
    * Neither the name of The Linux Foundation nor the names of its
      contributors may be used to endorse or promote products derived
      from this software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED "AS IS" AND ANY EXPRESS OR IMPLIED
   WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NON-INFRINGEMENT
   ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS
   BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
   CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
   SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR
   BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
   WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE
   OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN
   IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include <stdlib.h>
#include <unistd.h>

#include <android-base/logging.h>
#include <cutils/properties.h>
#include "vendor_init.h"

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>

void property_override(char const prop[], char const value[])
{
    prop_info *pi;

    pi = (prop_info*) __system_property_find(prop);
    if (pi)
        __system_property_update(pi, value, strlen(value));
    else
        __system_property_add(prop, strlen(prop), value, strlen(value));
}

void property_override_dual(char const system_prop[], char const vendor_prop[], char const value[])
{
    property_override(system_prop, value);
    property_override(vendor_prop, value);
}

void vendor_load_properties()
{
    char platform[PROP_VALUE_MAX];
    char bootmid[PROP_VALUE_MAX];
    char bootcid[PROP_VALUE_MAX];
    char device[PROP_VALUE_MAX];
    int rc;

    rc = property_get("ro.board.platform", platform, NULL);
    if (!rc || strncmp(platform, ANDROID_TARGET, PROP_VALUE_MAX))
        return;

    property_get("ro.boot.mid", bootmid, NULL);
    property_get("ro.boot.cid", bootcid, NULL);
// 
//     if (strstr(bootmid, "2PZF10000")) {
        /* Europe (OCE_UHL) */
        property_override_dual("ro.build.product", "ro.vendor.build.product", "htc_oceuhl");
        property_override_dual("ro.product.model", "ro.vendor.product.model", "HTC U Ultra");
property_override("ro.product.device", "htc_oceuhl");
//     } else if (strstr(bootmid, "2PZF20000")) {
//         /* Dual SIM Dual Netcom UHL Europe Africa Asia (OCE_DUGL) */
//         property_override_dual("ro.build.product", "ro.vendor.build.product", "htc_ocedugl");
//         property_override_dual("ro.product.model", "ro.vendor.product.model", "HTC_U-1u");
//     } else if (strstr(bootmid, "2PZF30000")) {
//         /* Dual card full Netcom UHL China (OCE_DUGL) */
//         property_override_dual("ro.build.product", "ro.vendor.build.product", "htc_ocedugl");
//         property_override_dual("ro.product.model", "ro.vendor.product.model", "HTC_U-1w");
//     } else {
//         /* GSM (OCE_UL) */
//         property_override_dual("ro.build.product", "ro.vendor.build.product", "htc_oceul");
//         property_override_dual("ro.product.model", "ro.vendor.product.model", "HTC U Ultra");
//     }

    property_get("ro.product.device", device, NULL);
    LOG(ERROR) << "Found bootmid " << bootmid << " setting build properties for " << device << " device\n";
}
