include_directories(
        ${PROJECT_SOURCE_DIR}/include
)

add_executable(pdCalc-cli pdCalc-simple-cli.cpp)
target_link_libraries(pdCalc-cli base)