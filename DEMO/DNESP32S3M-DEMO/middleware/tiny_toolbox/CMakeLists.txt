set(src_dirs
    .
    time
)

set(include_dirs
    .
    time
)

set(requires
    esp_timer
    esp_rtc
    espressif__esp-dsp
)

idf_component_register(SRC_DIRS ${src_dirs} INCLUDE_DIRS ${include_dirs} REQUIRES ${requires})
