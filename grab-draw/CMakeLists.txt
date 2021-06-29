df_standard_exe(grab-draw
    INCLUDE_DIRS /opt/pylon/include
    LINK_DIRS /opt/pylon/lib
    LINK_OPTIONS -Wl,-E
    LIBRARIES
        Qt5::Widgets
        pylonbase
        pylonutility
        GenApi_gcc_v3_1_Basler_pylon
        GCBase_gcc_v3_1_Basler_pylon
)
