cmake_minimum_required(VERSION 3.12)
project(CG_RayTracer C)

set(CMAKE_C_STANDARD 11)

### Begin Third-party
set (EXTERNAL_PATH ${CMAKE_CURRENT_SOURCE_DIR}/third-party)
set (EXTERNAL_INCLUDES)
set (EXTERNAL_LIBRARIES)

# Zlib
set(EXTERNAL_PATH_ZLIB ${EXTERNAL_PATH}/zlib-1.2.11)
add_subdirectory(${EXTERNAL_PATH_ZLIB})
list (APPEND EXTERNAL_INCLUDES ${EXTERNAL_PATH_ZLIB})
list (APPEND EXTERNAL_LIBRARIES zlibstatic)

# PNG
set(SKIP_INSTALL_ALL ON)
set(ZLIB_INCLUDE_DIR ${EXTERNAL_PATH}/zlib-1.2.11)
set(ZLIB_LIBRARY zlibstatic)
set(PNG_BUILD_ZLIB ON)
set(PNG_SHARED OFF)
set(PNG_TESTS OFF)
set(EXTERNAL_PATH_LIBPNG ${EXTERNAL_PATH}/lpng1636)
add_subdirectory(${EXTERNAL_PATH_LIBPNG})
list (APPEND EXTERNAL_INCLUDES ${EXTERNAL_PATH_LIBPNG})
list (APPEND EXTERNAL_LIBRARIES png_static)

### End Third-party

add_executable(CG_RayTracer main.c types.h
        png_render.h png_render.c
        vector.h vector.c
        color.h color.c
        matrix.h matrix.c
        scene.h scene.c
        ray.h ray.c)
target_include_directories(CG_RayTracer PRIVATE ${EXTERNAL_INCLUDES})
target_link_libraries(CG_RayTracer PRIVATE ${EXTERNAL_LIBRARIES})


