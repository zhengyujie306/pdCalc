include_directories(
    ${PROJECT_SOURCE_DIR}/include
)
aux_source_directory(. LIB_SRCS)
add_library(base ${LIB_SRCS})