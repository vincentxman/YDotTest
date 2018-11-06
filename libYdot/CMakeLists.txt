# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

#set_target_properties(Ydot-lib PROPERTIES COMPILE_DEFINITIONS "YDOT_LIB=1")
#set_target_properties(Ydot-lib PROPERTIES COMPILE_DEFINITIONS "WirePen")
aux_source_directory (I:/caiOid/Lib_2dCode/_yDotC/src  SRCS_LIB_DIR)
aux_source_directory (src/main/jni SRCS_LIB_DIR)

include_directories(I:/caiOid/Lib_2dCode/_nTree)
include_directories(I:/caiOid/Lib_2dCode/_yDotC/src)

add_definitions(-DYDOT_LIB=1 -DANDROID_LIB=1 -DWirePen=1)

add_library( # Sets the name of the library.
        Ydot-lib

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        I:/caiOid/Lib_2dCode/_nTree/IDKey.c
        ${SRCS_LIB_DIR})



# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
        log-lib

        # Specifies the name of the NDK library that
        # you want CMake to locate.
        log)

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

target_link_libraries( # Specifies the target library.
        Ydot-lib

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})