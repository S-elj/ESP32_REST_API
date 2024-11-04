Import("env")

import os

# Set default values if environment variables are missing
wifi_ssid = os.getenv("WIFI_SSID", "<CI>")
wifi_password = os.getenv("WIFI_PASSWORD", "<CI>")

# Pass these as build flags
env.Append(
    BUILD_FLAGS=[
        f'-D WIFI_SSID="{wifi_ssid}"',
        f'-D WIFI_PASSWORD="{wifi_password}"'
    ]
)

