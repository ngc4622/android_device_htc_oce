/*
   Copyright (c) 2013, The Linux Foundation. All rights reserved.

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
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/mount.h>

/*
Nougat        7.1   API level 25 | .cpp | int property_set(const char *name, const char *value); std::string property_get(const char* name);
Nougat        7.0   API level 24 | .cpp | int property_set(const char *name, const char *value); std::string property_get(const char* name);
Marshmallow   6.0   API level 23 | .cpp | int property_set(const char *name, const char *value); int property_get(const char *name, char *value);
Lollipop      5.1   API level 22 | .c   | int property_set(const char *name, const char *value); int property_get(const char *name, char *value);
Lollipop      5.0   API level 21
KitKat        4.4.4 API level 19
*/

#if PLATFORM_SDK_VERSION < 23
    extern "C" {
    #include "property_service.h"
    }
#else
    #include "property_service.h"
#endif


#include "init_htcCommon.h"


#if PLATFORM_SDK_VERSION > 23
    int property_get_sdk23(const char *key, char *value)
    {
        std::string propvalue;
        propvalue = property_get(key);
        strcpy(value, propvalue.c_str());
        return propvalue.length();
    }
#else
    // not very efficient but it's the easiest way (?)
    int property_get_sdk23(const char *key, char *value)
    {
        int rc;
        char propvalue[PROP_VALUE_MAX];
        rc = property_get(key, propvalue);
        if (rc)
            strcpy(value, propvalue);
        else
            value[0] = 0;
        return rc;
    }
#endif


#ifndef DEV_BLOCK_SYSTEM
#define DEV_BLOCK_SYSTEM "/dev/block/bootdevice/by-name/system"
#endif
static char * find_system_from_fstab(void)
{
    //TODO: parse fstab instead of using the hardcoded path
    return strdup(DEV_BLOCK_SYSTEM);
}

static void set_props_from_file(const char *filename)
{
    FILE *fp = fopen(filename, "r");

    if (fp) {
        char line[1024];

        char propname[PROP_NAME_MAX];
        char propvalue[PROP_VALUE_MAX];
        char *pch;

        while ((fgets(line, sizeof(line), fp))) {
            if (line[0] == '\n' || line[0] == '#') continue;

            pch = strtok(line, "=\n");
            if (!pch || strlen(pch) >= PROP_NAME_MAX) continue;
            strcpy(propname, pch);

            pch = strtok(NULL, "=\n");
            if (!pch || strlen(pch) >= PROP_VALUE_MAX) continue;
            strcpy(propvalue, pch);

            if (!strcmp(propname, "ro.build.fingerprint") || !strcmp(propname, "ro.product.device"))
                property_set(propname, propvalue);
        }
        fclose(fp);
    }
}

static void set_ro_product_device(void)
{
    char propvalue[PROP_VALUE_MAX];

    if (!property_get_sdk23("ro.product.device", propvalue)) {
        property_get_sdk23("ro.build.product", propvalue);
        property_set("ro.product.device", propvalue);
    }
}

void set_props_from_build(void)
{
    if (access("/system/build.prop", R_OK) == 0)
        set_props_from_file("/system/build.prop");

    else if (mkdir("/tmpsys", 777) == 0) {
        char *system_blk_dev = find_system_from_fstab();

        if (system_blk_dev) {
            int is_mounted = mount(system_blk_dev, "/tmpsys", "ext4", MS_RDONLY | MS_NOATIME , "") == 0;

            if (!is_mounted)
                is_mounted = mount(system_blk_dev, "/tmpsys", "f2fs", MS_RDONLY | MS_NOATIME , "") == 0;

            if (is_mounted) {
                set_props_from_file("/tmpsys/build.prop");
                umount("/tmpsys");
            }
            free(system_blk_dev);
        }
        rmdir("/tmpsys");
    }

    set_ro_product_device();
}
