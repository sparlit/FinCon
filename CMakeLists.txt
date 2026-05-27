cmake_minimum_required(VERSION 3.27)
project(FinConTerminal VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# Optimization
find_program(CCACHE_PROGRAM ccache)
if(CCACHE_PROGRAM)
    set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif()

# Qt6 Find
find_package(Qt6 REQUIRED COMPONENTS
    Widgets
    Charts
    Network
    WebSockets
    Sql
    PrintSupport
    Multimedia
    TextToSpeech
    Test
)

include(FetchContent)

# Advanced Docking System
FetchContent_Declare(
  qtads
  GIT_REPOSITORY https://github.com/githubuser0xFFFF/Qt-Advanced-Docking-System.git
  GIT_TAG        4.3.1
)

# QXlsx for Excel Grid
FetchContent_Declare(
  QXlsx
  GIT_REPOSITORY https://github.com/QtExcel/QXlsx.git
  GIT_TAG        v1.4.9
  SOURCE_SUBDIR  QXlsx
)
FetchContent_MakeAvailable(qtads QXlsx)

# Sources
set(SOURCES
    src/main.cpp
    src/core/Logger.cpp
    src/core/CrashHandler.cpp
    src/core/ThemeManager.cpp
    src/core/DataHub.cpp
    src/core/Persistence.cpp
    src/core/MockQuoteProducer.cpp
    src/core/CredentialManager.cpp
    src/services/AuthService.cpp
    src/services/PythonRunner.cpp
    src/ui/MainWindow.cpp
    src/ui/CommandBar.cpp
    src/ui/Sidebar.cpp
    src/ui/StatusBar.cpp
    src/ui/NavigationBar.cpp
    src/screens/ScreenFactory.cpp
    src/screens/Screens.cpp
    src/screens/NodeEditorScreen.cpp
    src/screens/QuantLibSuiteScreen.cpp
    src/screens/IScreen.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_link_libraries(${PROJECT_NAME} PRIVATE
    Qt6::Widgets
    Qt6::Charts
    Qt6::Network
    Qt6::WebSockets
    Qt6::Sql
    Qt6::PrintSupport
    Qt6::Multimedia
    Qt6::TextToSpeech
    qt6advanceddocking
    QXlsx
)

target_include_directories(${PROJECT_NAME} PRIVATE src)

# Tests
add_executable(FinConTests
    src/tests/FinConSystemTests.cpp
    src/core/DataHub.cpp
    src/core/Logger.cpp
    src/core/Persistence.cpp
)
target_link_libraries(FinConTests PRIVATE
    Qt6::Test
    Qt6::Sql
)
target_include_directories(FinConTests PRIVATE src)

if(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE "-framework Foundation" "-framework Security")
elseif(UNIX AND NOT APPLE)
    find_package(PkgConfig REQUIRED)
    pkg_check_modules(LIBSECRET REQUIRED libsecret-1)
    target_link_libraries(${PROJECT_NAME} PRIVATE ${LIBSECRET_LIBRARIES})
    target_include_directories(${PROJECT_NAME} PRIVATE ${LIBSECRET_INCLUDE_DIRS})
endif()
