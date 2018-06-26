/*
   Copyright (C) 2013, The Linux Foundation. All rights reserved.
   Copyright (C) 2017 The Android Open Source Project

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

#include "vendor_init.h"
#include "property_service.h"
#include "log.h"
#include "util.h"

#include "init_htcCommon.h"

void vendor_load_properties()
{
    char platform[PROP_VALUE_MAX];
    char bootmid[PROP_VALUE_MAX];
    char bootcid[PROP_VALUE_MAX];
    char device[PROP_VALUE_MAX];
    int rc;

    rc = property_get_sdk23("ro.board.platform", platform);
    if (!rc || strncmp(platform, ANDROID_TARGET, PROP_VALUE_MAX))
        return;

    property_get_sdk23("ro.boot.mid", bootmid);
    property_get_sdk23("ro.boot.cid", bootcid);

    if (strstr(bootmid, "2PZF10000")) {
        /* Europe (OCE_UHL) */
        property_set("ro.build.product", "htc_oceuhl");
        property_set("ro.product.model", "HTC U Ultra");
    } else if (strstr(bootmid, "2PZF20000")) {
        /* Dual SIM Dual Netcom UHL Europe Africa Asia (OCE_DUGL) */
        property_set("ro.build.product", "htc_ocedugl");
        property_set("ro.product.model", "HTC_U-1u");
    } else if (strstr(bootmid, "2PZF30000")) {
        /* Dual card full Netcom UHL China (OCE_DUGL) */
        property_set("ro.build.product", "htc_ocedugl");
        property_set("ro.product.model", "HTC_U-1w");
    } else {
        /* GSM (OCE_UL) */
        property_set("ro.build.product", "htc_oceul");
        property_set("ro.product.model", "HTC U Ultra");
    }

    set_props_from_build();

    property_get_sdk23("ro.product.device", device);
    ERROR("Found bootmid %s setting build properties for %s device\n", bootmid, device);
}
