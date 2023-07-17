/*
 * Copyright (C) 2021 The LineageOS Project
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#include <cstdlib>
#include <fstream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/sysinfo.h>

#define _REALLY_INCLUDE_SYS__SYSTEM_PROPERTIES_H_
#include <sys/_system_properties.h>
#include <android-base/file.h>
#include <android-base/properties.h>
#include <android-base/strings.h>

#include "property_service.h"
#include "vendor_init.h"

using android::base::GetProperty;
using std::string;
using android::base::ReadFileToString;
using android::base::Trim;

__attribute__ ((weak))
void init_target_properties() {}

string heapstartsize, heapgrowthlimit, heapsize,
       heapminfree, heapmaxfree, heaptargetutilization;

void property_override(string prop, string value)
{
    auto pi = (prop_info*) __system_property_find(prop.c_str());
    if (pi != nullptr)
        __system_property_update(pi, value.c_str(), value.size());
        __system_property_add(prop.c_str(), prop.size(), value.c_str(), value.size());
}

void check_device()
{
    struct sysinfo sys;

    sysinfo(&sys);

    if (sys.totalram > 3072ull * 1024 * 1024) {
        // from - phone-xhdpi-4096-dalvik-heap.mk // increased heapgrowthlimit
        heapgrowthlimit = "256m";
        heapsize = "512m";
        heaptargetutilization = "0.6";
        heapminfree = "8m";
        heapmaxfree = "16m";
    } else if (sys.totalram > 2048ull * 1024 * 1024) {
        // from - custom (adapted 2048-4096 values)
        heapgrowthlimit = "192m";
        heapsize = "512m";
        heaptargetutilization = "0.75";
        heapminfree = "2m";
        heapmaxfree = "8m";
    } else {
        // from - phone-xhdpi-2048-dalvik-heap.mk
        heapgrowthlimit = "128m";
        heapsize = "256m";
        heaptargetutilization = "0.75";
        heapminfree = "512k";
        heapmaxfree = "8m";
   }
}

void low_ram_device()
{
    struct sysinfo sys;
    sysinfo(&sys);

    if (sys.totalram <= 2048ull * 1024 * 1024) {
        // Generated from build/make/target/product/go_defaults_common.mk
        property_override("ro.config.low_ram", "true");
        property_override("ro.config.avoid_gfx_accel", "true");
    }
}

void vendor_load_properties()
{
    check_device();
    low_ram_device();

    property_override("dalvik.vm.heapstartsize", "8m");
    property_override("dalvik.vm.heapgrowthlimit", heapgrowthlimit);
    property_override("dalvik.vm.heapsize", heapsize);
    property_override("dalvik.vm.heaptargetutilization", heaptargetutilization);
    property_override("dalvik.vm.heapminfree", heapminfree);
    property_override("dalvik.vm.heapmaxfree", heapmaxfree);

    init_target_properties();
}