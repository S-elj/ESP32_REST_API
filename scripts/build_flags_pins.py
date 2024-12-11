Import("env")

config = env.GetProjectConfig()

# Set default values if environment variables are missing
led_pin = config.get("env", "led_pin", default="0")
photocell_pin = config.get("env", "photocell_pin", default="0")
thermistor_pin = config.get("env", "thermistor_pin", default="0")

# Add additional escaping for special characters in build flags
env.Append(
    BUILD_FLAGS=[
        f'-D LED_PIN={led_pin}',
        f'-D PHOTOCELL_PIN={photocell_pin}',
        f'-D THERMISTOR_PIN={thermistor_pin}'
    ]
)
