## - Examples using and Qt5

if(OPTION_BUILD_GLFW)
    add_subdirectory(gui/glfw)    
elseif(OPTION_BUILD_Qt5)
    add_subdirectory(gui/qt5)
elseif(OPTION_BUILD_Qt6)
   add_subdirectory(gui/qt6)
else()
    message("Nothing to build")
endif()   
 