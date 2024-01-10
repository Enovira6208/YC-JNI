# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.10.2)

# Declares and names the project.


# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

add_library(
        # Sets the name of the library.
        dc

        # Sets the library as a shared library.
        SHARED

        # Provides a relative path to your source file(s).
        native-lib.cpp
        Protocol/BBC6638.c
        Protocol/BZC3395.c
        Protocol/DDC8910.c
        Protocol/DS_2000D.c
        Protocol/FH_ai_6000h.c
        Protocol/FH_ai_6000hl.c
        Protocol/FH_ai_6000r.c
        Protocol/FH_ai_6106s.c
        Protocol/FH_ai_6301.c
        Protocol/FH_ai_6310B.c
        Protocol/FH_ai_6310L.c
        Protocol/FH_ai_6600C.c
        Protocol/JHMD3_jh6000.c
        Protocol/TD_3310C_YZFJ.c
        Protocol/TD_3310C_ZK.c
        Protocol/TD_3310C_ZLDZ.c
        Protocol/HCYZ_iv.c
        Protocol/HLC5501.c
        Protocol/jh6000.c
        Protocol/JHLK_100.c
        Protocol/JYK_I.c
        Protocol/JYL_100B.c
        Protocol/JYR_20s.c
        Protocol/JYR_40s.c
        Protocol/JYR_40c.c
        Protocol/JYT_A_V0.c
        Protocol/JYT_A_V1.c
        Protocol/JYT_A_V2.c
        Protocol/PDT_840.c
        Protocol/JYW6100.c
        Protocol/FH_ai_6301B.c
        Protocol/FH_ai_6301_general.c
        Protocol/CTP_120.c
        Protocol/SD_HVM_5000.c
        Protocol/JYW6400_DC.c
        Protocol/SD_Z_VI.c
        Protocol/JYW6400_IM.c
        Protocol/JYC.c
        Protocol/JD11.c
        Protocol/CM2100D.c
        Protocol/QGDW_5_8.c
        Protocol/QGDW_5_19.c
        Protocol/FH_IDCE_2415CT.c
        Protocol/BYKC_2003.c
        Protocol/HV9003.c
        Protocol/JYR_40D.c
        Protocol/FH_ai_6103z.c
        public/cJSON.c
        public/interface.c
        public/mycrc16.c
        public/public.c
        )

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
        dc

        # Links the target library to the log library
        # included in the NDK.
        ${log-lib})