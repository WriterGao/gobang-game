cmake_minimum_required(VERSION 3.16)
project(Gobang VERSION 1.0.0 LANGUAGES CXX)

# 设置C++标准
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 查找Qt5
find_package(Qt5 REQUIRED COMPONENTS Core Widgets Gui Multimedia MultimediaWidgets Concurrent)

# 设置Qt MOC
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

# 包含目录
include_directories(${CMAKE_CURRENT_SOURCE_DIR}/src)

# 源文件
set(SOURCES
    src/main.cpp
    src/core/GameEngine.cpp
    src/core/ChessBoard.cpp
    src/core/GameRule.cpp
    src/core/Player.cpp
    src/ui/MainWindow.cpp
    src/ui/GameWidget.cpp
    src/ui/SettingsDialog.cpp
    src/managers/ConfigManager.cpp
    src/managers/AudioManager.cpp
    src/ai/AIPlayer.cpp
    src/ai/MinimaxAI.cpp
)

# 头文件
set(HEADERS
    src/core/GameEngine.h
    src/core/ChessBoard.h
    src/core/GameRule.h
    src/core/Player.h
    src/ui/MainWindow.h
    src/ui/GameWidget.h
    src/ui/SettingsDialog.h
    src/managers/ConfigManager.h
    src/managers/AudioManager.h
    src/ai/AIPlayer.h
    src/ai/MinimaxAI.h
)

# 创建可执行文件
add_executable(Gobang ${SOURCES} ${HEADERS})

# 链接Qt库
target_link_libraries(Gobang Qt5::Core Qt5::Widgets Qt5::Gui Qt5::Multimedia Qt5::MultimediaWidgets Qt5::Concurrent)

# 设置输出目录
set_target_properties(Gobang PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin
)

# 编译选项
if(MSVC)
    target_compile_options(Gobang PRIVATE /W4)
else()
    target_compile_options(Gobang PRIVATE -Wall -Wextra -Wpedantic)
endif()

# 设置应用程序信息
set_target_properties(Gobang PROPERTIES
    MACOSX_BUNDLE TRUE
    MACOSX_BUNDLE_INFO_PLIST ${CMAKE_SOURCE_DIR}/Info.plist.in
    MACOSX_BUNDLE_BUNDLE_NAME "五子棋游戏"
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION}
    MACOSX_BUNDLE_IDENTIFIER "com.gobang.game"
    WIN32_EXECUTABLE TRUE
)

# 安装规则
if(APPLE)
    install(TARGETS Gobang 
        BUNDLE DESTINATION . 
        RUNTIME DESTINATION bin
    )
    # 复制资源文件
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/resources/
        DESTINATION Gobang.app/Contents/Resources
        OPTIONAL
    )
elseif(WIN32)
    install(TARGETS Gobang 
        RUNTIME DESTINATION bin
        LIBRARY DESTINATION lib
        ARCHIVE DESTINATION lib
    )
    # Windows资源
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/resources/
        DESTINATION bin/resources
        OPTIONAL
    )
else()
    # Linux
    install(TARGETS Gobang DESTINATION bin)
    install(DIRECTORY ${CMAKE_SOURCE_DIR}/resources/
        DESTINATION share/gobang/resources
        OPTIONAL
    )
    # Linux desktop文件
    install(FILES ${CMAKE_SOURCE_DIR}/gobang.desktop
        DESTINATION share/applications
        OPTIONAL
    )
endif()

# CPack配置
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_NAME "五子棋游戏")
set(CPACK_PACKAGE_VENDOR "Gobang Game Studio")
set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "一个功能完整的五子棋游戏")
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION})
set(CPACK_PACKAGE_VERSION_MAJOR "1")
set(CPACK_PACKAGE_VERSION_MINOR "0")
set(CPACK_PACKAGE_VERSION_PATCH "0")
set(CPACK_PACKAGE_INSTALL_DIRECTORY "五子棋游戏")

if(APPLE)
    set(CPACK_GENERATOR "DragNDrop")
    set(CPACK_DMG_FORMAT "UDZO")
    set(CPACK_DMG_VOLUME_NAME "五子棋游戏")
    set(CPACK_SYSTEM_NAME "macOS")
elseif(WIN32)
    set(CPACK_GENERATOR "NSIS")
    set(CPACK_NSIS_PACKAGE_NAME "五子棋游戏")
    set(CPACK_NSIS_DISPLAY_NAME "五子棋游戏 v${PROJECT_VERSION}")
    set(CPACK_NSIS_CONTACT "support@gobang.game")
    set(CPACK_NSIS_URL_INFO_ABOUT "https://github.com/gobang-game")
    set(CPACK_SYSTEM_NAME "Windows")
else()
    set(CPACK_GENERATOR "DEB;RPM;TGZ")
    set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Gobang Game Studio")
    set(CPACK_DEBIAN_PACKAGE_DEPENDS "libqt5core5a, libqt5gui5, libqt5widgets5, libqt5multimedia5")
    set(CPACK_RPM_PACKAGE_LICENSE "MIT")
    set(CPACK_SYSTEM_NAME "Linux")
endif()

include(CPack) 