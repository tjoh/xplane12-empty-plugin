cmake_minimum_required(VERSION 3.18)

project(empty-plugin LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_compile_definitions(PLUGIN_NAME="${PROJECT_NAME}")

set(sdk_base SDK)
include_directories(${sdk_base}/CHeaders/XPLM/)

message(STATUS "Setup for Linux")
add_compile_definitions(APL=0 IBM=0 LIN=1)
set(xpl_name lin.xpl)


add_compile_definitions(XPLM200 XPLM210 XPLM300 XPLM301 XPLM302 XPLM303 XPLM400)

if (CMAKE_CXX_COMPILER_ID STREQUAL "Clang" OR CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
    message(STATUS "Setup for GCC")
    add_compile_options(-rdynamic -nodefaultlibs -undefined_warning -fvisibility=hidden)
    add_compile_options(-Wall -Wextra -Wpedantic)
endif ()

add_subdirectory(src)

set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "")
set_target_properties(${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${xpl_name})
set_target_properties(${PROJECT_NAME} PROPERTIES SUFFIX "")

install(TARGETS ${PROJECT_NAME}
    DESTINATION ${PROJECT_NAME}
    PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE GROUP_READ GROUP_EXECUTE WORLD_READ WORLD_EXECUTE
)
