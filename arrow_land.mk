#
# Copyright (C) 2017-2021 The LineageOS Project
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

# Inherit from those products. Most specific first.
$(call inherit-product, $(SRC_TARGET_DIR)/product/core_64_bit.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/full_base_telephony.mk)
$(call inherit-product, $(SRC_TARGET_DIR)/product/product_launched_with_m.mk)

# Inherit some common from Octavi OS Project stuff
$(call inherit-product, vendor/arrow/config/common.mk)

# Inherit from land device
$(call inherit-product, $(LOCAL_PATH)/device.mk)

# Bootanimation
TARGET_BOOT_ANIMATION_RES := 720

# Extra's
TARGET_FACE_UNLOCK_SUPPORTED := true
TARGET_SUPPORTS_GOOGLE_RECORDER := false
TARGET_INCLUDE_STOCK_ARCORE := true
TARGET_INCLUDE_LIVE_WALLPAPERS := false

USE_PIXEL_CHARGER := true

# Gapps
# TARGET_GAPPS_ARCH := arm64
# TARGET_INCLUDE_STOCK_ARCORE := true
# ARROW_GAPPS := true

TARGET_FACE_UNLOCK_SUPPORTED := true
TARGET_SUPPORTS_GOOGLE_RECORDER := false
TARGET_INCLUDE_LIVE_WALLPAPERS := false

# Device identifier
PRODUCT_DEVICE := land
PRODUCT_NAME := arrow_land
PRODUCT_BRAND := Xiaomi
PRODUCT_MODEL := Redmi 3S
PRODUCT_MANUFACTURER := Xiaomi
TARGET_VENDOR := Xiaomi
BOARD_VENDOR := Xiaomi

PRODUCT_GMS_CLIENTID_BASE := android-xiaomi

PRODUCT_BUILD_PROP_OVERRIDES += \
    PRIVATE_BUILD_DESC="land-user 6.0.1 MMB29M V10.2.2.0.MALMIXM release-keys"

# Set BUILD_FINGERPRINT variable to be picked up by both system and vendor build.prop
BUILD_FINGERPRINT := "Xiaomi/land/land:6.0.1/MMB29M/V10.2.2.0.MALMIXM:user/release-keys"
