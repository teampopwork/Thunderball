project(Thunderball LANGUAGES CXX)

add_executable(popcapgame1 WIN32
    AdventureScreen.cpp
    Board.cpp
    CharacterMgr.cpp
    ConfigParser.cpp
    DataSync.cpp
    GameStats.cpp
    HelpScreen.cpp
    LevelEditor.cpp
    LoadTimer.cpp
    LoadingScreen.cpp
    Main.cpp
    MainMenu.cpp
    NewUserDialog.cpp
    OptionsDialog.cpp
    PlayerInfo.cpp
    PhysObj.cpp
    Poly.cpp
    Line.cpp
    Brick.cpp
    Ball.cpp
    AIBall.cpp
    Hole.cpp
    ProfileMgr.cpp
    Res.cpp
    SimpleButton.cpp
    StageMgr.cpp
    StatsMgr.cpp
    LogicMgr.cpp
    HighScoreMgr.cpp
    ImageMgr.cpp
    StoryScreen.cpp
    LevelScreen.cpp
    ThunderCommon.cpp
    ThunderButton.cpp
    ThunderCheckbox.cpp
    ThunderDialog.cpp
    ThunderSlider.cpp
    ThunderballApp.cpp
    TrophyMgr.cpp
    TrophyScreen.cpp
    UpsellScreen.cpp
    UserDialog.cpp
    WidgetMover.cpp
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
