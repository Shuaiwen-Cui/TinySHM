set(src_dirs
    .
    constants
)

set(include_dirs
    .
    constants
)

set(requires
    tiny_toolbox
)

idf_component_register(SRC_DIRS ${src_dirs} INCLUDE_DIRS ${include_dirs} REQUIRES ${requires})
