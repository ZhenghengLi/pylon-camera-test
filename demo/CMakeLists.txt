df_standard_exe(demo
    INCLUDE_DIRS /opt/pylon/include
    LINK_DIRS /opt/pylon/lib
    LINK_OPTIONS -Wl,-E
    LIBRARIES
        pylonbase
        pylonutility
        GenApi_gcc_v3_1_Basler_pylon
        GCBase_gcc_v3_1_Basler_pylon
)
