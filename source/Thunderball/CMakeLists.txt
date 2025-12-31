project(Thunderball LANGUAGES CXX)

add_executable(popcapgame1 WIN32
    ThunderCommon.cpp
    ThunderballApp.cpp
    ThunderButton.cpp
    ThunderCheckbox.cpp
    ThunderDialog.cpp
    WidgetMover.cpp
    LoadingScreen.cpp
    Res.cpp
    Main.cpp
    DataSync.cpp
)

target_include_directories(popcapgame1 PRIVATE
    ${SEXYAPP_INCLUDE_DIRS}
    ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdparty/directx9/Include
)

if(MSYS OR MINGW)
    target_link_libraries(popcapgame1 -static-libgcc -static-libstdc++)
endif()

if(MSVC)
    target_link_options(popcapgame1 PRIVATE /INCREMENTAL:NO /DEBUG /OPT:REF /OPT:ICF /SUBSYSTEM:WINDOWS /pdb:${CMAKE_CURRENT_BINARY_DIR}/popcapgame1.pdb)
endif()

target_link_libraries(popcapgame1 SexyAppFramework)