set(src_dirs
    .
    vec
)

set(include_dirs
    .
    include
    vec
)

set(requires
    tiny_toolbox
)

idf_component_register(SRC_DIRS ${src_dirs} INCLUDE_DIRS ${include_dirs} REQUIRES ${requires})
