project(ejemplo1)
cmake_minimum_required(VERSION 2.6)
find_package(Qt4 REQUIRED)

include_directories(${QT_INCLUDES} ${CMAKE_CURRENT_BINARY_DIR})

# Sources set
SET ( SOURCES
  ${SOURCES}
  main.cpp
  hebras.cpp
 )

# Headers set
SET ( HEADERS
  ${HEADERS}
  hebras.h
)

ADD_DEFINITIONS(-std=c++14)

FIND_PACKAGE( Qt4 REQUIRED )
SET( QT_USE_QTGUI TRUE )
QT4_WRAP_CPP( MOC_SOURCES ${HEADERS} )
QT4_WRAP_UI( UI_HEADERS counterDlg.ui )

ADD_EXECUTABLE(ejemplo1 ${SOURCES}  ${MOC_SOURCES} ${UI_HEADERS})
target_link_libraries(ejemplo1 ${QT_QTCORE_LIBRARY} ${QT_QTGUI_LIBRARY} -lpthread)
install(TARGETS ejemplo1 RUNTIME DESTINATION bin)
