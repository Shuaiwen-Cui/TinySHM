set(src_dirs
    .
)

set(include_dirs
    .
    include
)

set(requires
    tiny_toolbox
    tiny_math
    tiny_dsp
)

idf_component_register(SRC_DIRS ${src_dirs} INCLUDE_DIRS ${include_dirs} REQUIRES ${requires})