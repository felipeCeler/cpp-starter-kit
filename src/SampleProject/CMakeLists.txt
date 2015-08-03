project(${CMAKE_PROJECT_NAME}_EXE)

find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Widgets REQUIRED)

find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)

include_directories(
        ## - OpenGL 
        ${GLEW_INCLUDE_DIR}
        ${OPENGL_INCLUDE_DIR}
        ## - Qt5
        ${Qt5Widgets_INCLUDE_DIRS}
        ${Qt5OpenGL_INCLUDE_DIRS}
        )

include_directories (
  ${CMAKE_CURRENT_SOURCE_DIR}
  ${CMAKE_CURRENT_BINARY_DIR}
)

## Show all include directories
get_property(dirs DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY INCLUDE_DIRECTORIES)
foreach(dir ${dirs})
  message(STATUS "dir='${dir}'")
endforeach()

set( ${PROJECT_NAME}_SOURCES GUI/Qt/QtSampleProject.cpp  ## File where the main function resides
    						 GUI/Qt/MainWindow/MainWindow.cpp
    						 GUI/Qt/GLWidget/GLWidget.cpp
    						 GUI/Qt/AboutWidget/AboutWidget.cpp
    						 )
	
set( ${PROJECT_NAME}_HEADERS GUI/Qt/MainWindow/MainWindow.hpp
                             GUI/Qt/GLWidget/GLWidget.hpp
                             GUI/Qt/AboutWidget/AboutWidget.hpp
                            )	
## Q_OBJECT files
set( MOC_HEADERS GUI/Qt/MainWindow/MainWindow.hpp
                 GUI/Qt/GLWidget/GLWidget.hpp
                 GUI/Qt/AboutWidget/AboutWidget.hpp  
                 )
## Qt Designer Ui files                 
set( UI_SOURCES GUI/Qt/MainWindow/${CMAKE_PROJECT_NAME}.ui GUI/Qt/AboutWidget/AboutWidget.ui )
## Resources
set(RCC_SOURCES GUI/Qt/RCC/Resources.qrc)

QT5_WRAP_CPP( MOC_SOURCES ${MOC_HEADERS})
QT5_WRAP_UI (UI_HEADERS ${UI_SOURCES})
QT5_ADD_RESOURCES(RCC_HEADERS ${RCC_SOURCES})

IF(WIN32)
	ADD_EXECUTABLE(${CMAKE_PROJECT_NAME} WIN32 ${${PROJECT_NAME}_SOURCES} ${${PROJECT_NAME}_HEADERS} ${MOC_SOURCES} ${UI_HEADERS} ${RCC_HEADERS})
ELSE(WIN32)
	ADD_EXECUTABLE(${CMAKE_PROJECT_NAME} ${${PROJECT_NAME}_SOURCES} ${${PROJECT_NAME}_HEADERS} ${MOC_SOURCES} ${UI_HEADERS} ${RCC_HEADERS})	
ENDIF(WIN32)
              
TARGET_LINK_LIBRARIES(${CMAKE_PROJECT_NAME}   Qt5::OpenGL Qt5::Widgets ${OPENGL_LIBRARIES}  ${GLEW_LIBRARY})
