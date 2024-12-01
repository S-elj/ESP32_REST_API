Import("env")

config = env.GetProjectConfig()

# Set default values if environment variables are missing
wifi_ssid = config.get("env", "wifi_ssid", default="CI")
wifi_password = config.get("env", "wifi_password", default="CI")

# Add additional escaping for special characters in build flags
env.Append(
    BUILD_FLAGS=[
        f'-D WIFI_SSID=\\\"{wifi_ssid}\\\"',
        f'-D WIFI_PASSWORD=\\\"{wifi_password}\\\"'
    ]
)
