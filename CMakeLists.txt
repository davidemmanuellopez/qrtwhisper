cmake_minimum_required(VERSION 3.16)

project(MyQtMVCProject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC OFF) # No usamos archivos .ui

set(WHISPER_EXAMPLES "/home/david/whisper.cpp/examples")

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(${PROJECT_NAME}
        main.cpp
        model.cpp model.h
        controller.cpp controller.h
        view.cpp view.h
)

target_include_directories(${PROJECT_NAME} PRIVATE ${WHISPER_EXAMPLES})
target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
