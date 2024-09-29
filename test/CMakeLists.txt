project(test)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)
aux_source_directory(src SRC_LIST)
include_directories(inc)
add_executable(test ${SRC_LIST})
# cmake -G "MinGW Makefiles" ..
# mingw32-make.exe