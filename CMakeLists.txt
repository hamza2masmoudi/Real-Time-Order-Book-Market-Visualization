cmake_minimum_required(VERSION 3.16)
project(orderbook LANGUAGES CXX)

# Set C++ Standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Enable Qt's automatic processing
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)  # ✅ Keep AUTORCC enabled (it will automatically handle .qrc files)

# Find required packages
find_package(Qt6 6.2 REQUIRED COMPONENTS Core Gui Widgets Charts)
find_package(CURL REQUIRED)
find_package(nlohmann_json REQUIRED)

# Include directories
include_directories(
    ${CMAKE_SOURCE_DIR}/backend
    ${CMAKE_SOURCE_DIR}/frontend
    ${CMAKE_SOURCE_DIR}/third_party
)

# Add executable target
add_executable(orderbook
    main.cpp
    backend/orderbook.cpp
    backend/matching_engine.cpp
    backend/market_data.cpp
    frontend/mainwindow.cpp
    resources.qrc  # ✅ Keep this in add_executable, so AUTORCC processes it
)



# Link necessary libraries
target_link_libraries(orderbook PRIVATE
    Qt6::Core
    Qt6::Gui
    Qt6::Widgets
    Qt6::Charts
    CURL::libcurl
    nlohmann_json::nlohmann_json
)