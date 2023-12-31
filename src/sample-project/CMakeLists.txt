## - Examples using and Qt5

if(OPTION_BUILD_GLFW)
    add_subdirectory(gui/glfw)    
endif()   

if(OPTION_BUILD_Qt5)
    #Historic
    add_subdirectory(gui/qt5)
endif()   

if(OPTION_BUILD_Qt6)
   add_subdirectory(gui/qt6)
endif()   


 