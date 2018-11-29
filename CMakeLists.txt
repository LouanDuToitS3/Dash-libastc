cmake_minimum_required (VERSION 3.5)
project(astc VERSION 1.0.0 LANGUAGES C CXX)

############################################################
# Files
############################################################
set(objsrc
    astc-encoder/Source/astc_averages_and_directions.cpp
    astc-encoder/Source/astc_block_sizes2.cpp
    astc-encoder/Source/astc_color_quantize.cpp
    astc-encoder/Source/astc_color_unquantize.cpp
    astc-encoder/Source/astc_compress_symbolic.cpp
    astc-encoder/Source/astc_decompress_symbolic.cpp
    astc-encoder/Source/astc_encoding_choice_error.cpp
    astc-encoder/Source/astc_find_best_partitioning.cpp
    astc-encoder/Source/astc_ideal_endpoints_and_weights.cpp
    astc-encoder/Source/astc_image_load_store.cpp
    astc-encoder/Source/astc_integer_sequence.cpp
    astc-encoder/Source/astc_ktx_dds.cpp
    astc-encoder/Source/astc_kmeans_partitioning.cpp
    astc-encoder/Source/astc_partition_tables.cpp
    astc-encoder/Source/astc_percentile_tables.cpp
    astc-encoder/Source/astc_pick_best_endpoint_format.cpp
    astc-encoder/Source/astc_quantization.cpp
    astc-encoder/Source/astc_stb_tga.cpp
    astc-encoder/Source/astc_symbolic_physical.cpp
    astc-encoder/Source/astc_toplevel.cpp
    astc-encoder/Source/astc_weight_align.cpp
    astc-encoder/Source/astc_weight_quant_xfer_tables.cpp
    astc-encoder/Source/astc_compute_variance.cpp
    astc-encoder/Source/mathlib.cpp
    astc-encoder/Source/softfloat.cpp
    astc-encoder/Source/astc_codec_internals.h
    astc-encoder/Source/mathlib.h
    astc-encoder/Source/softfloat.h
    astc-encoder/Source/stb_image.c
    astc.h
    astc.cpp
)

set(libhdr
    astc.h
)

set(libtest_src
    astc_libtest.cpp
)

include_directories( astc-encoder/Source )

if(WIN32)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}  /D_USE_MATH_DEFINES /D_CRT_SECURE_NO_WARNINGS" CACHE STRING "Set C++ Compiler Flags" FORCE)
else()
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O3 -Wall -W -Wextra -msse2 -mfpmath=sse" CACHE STRING "Set C++ Compiler Flags" FORCE)
endif()

############################################################
# Create libraries
############################################################
add_library(objlib OBJECT ${objsrc})
set_property(TARGET objlib PROPERTY POSITION_INDEPENDENT_CODE 1)
#target_compile_options(objlib PRIVATE -Dexit=myExit -Dmain=astc_main)
target_compile_options(objlib PRIVATE -Dmain=astc_main)

add_library(astc SHARED $<TARGET_OBJECTS:objlib>)
set_target_properties(astc PROPERTIES VERSION ${PROJECT_VERSION})
set_target_properties(astc PROPERTIES SOVERSION 1)

add_library(astc_static STATIC $<TARGET_OBJECTS:objlib>)

############################################################
# Create an test executable
############################################################
add_executable(astcenc_test ${libtest_src})
#set(CMAKE_THREAD_PREFER_PTHREAD TRUE)
find_package( Threads )
target_link_libraries(astcenc_test PRIVATE astc ${CMAKE_THREAD_LIBS_INIT})

############################################################
# Install
############################################################
include(GNUInstallDirs)

if(WIN32)
install(TARGETS astc RUNTIME DESTINATION ${CMAKE_INSTALL_LIBDIR} LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS astc_static ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${libhdr} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
else()
install(TARGETS astc LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(TARGETS astc_static ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
install(FILES ${libhdr} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
endif()  