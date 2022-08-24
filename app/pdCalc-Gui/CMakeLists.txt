include_directories(
        ${PROJECT_SOURCE_DIR}/include
)

add_executable(pdCalc-Gui pdCalc-simple-gui.cpp)
target_link_libraries(pdCalc-Gui base sfml-system sfml-graphics sfml-window)