cmake_minimum_required(VERSION 3.16)
project(orderbook LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Qt's automatic processing
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

find_package(Qt6 6.2 REQUIRED COMPONENTS Core Gui Widgets Charts)
find_package(spdlog REQUIRED)

include_directories(
    ${CMAKE_SOURCE_DIR}/backend
    ${CMAKE_SOURCE_DIR}/frontend
)

# 1) Compile the .qrc resource file
qt_add_resources(myResources resources.qrc)

add_executable(orderbook
    main.cpp
    backend/orderbook.cpp
    backend/matching_engine.cpp
    frontend/mainwindow.cpp
    #2) we add resource compilation result
    ${myResources}
)

target_link_libraries(orderbook PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Charts
    spdlog::spdlog
)