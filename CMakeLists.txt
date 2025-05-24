cmake_minimum_required(VERSION 3.16)

project(MyQtMVCProject VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC OFF) # No usamos archivos .ui

set(WHISPER_EXAMPLES "/home/david/whisper.cpp/examples")

find_package(Qt6 REQUIRED COMPONENTS Widgets)
set(SDL2_DIR /usr/lib/x86_64-linux-gnu/cmake/SDL2)


add_executable(${PROJECT_NAME}
        main.cpp
        model.cpp model.h
        controller.cpp controller.h
        view.cpp view.h
)



add_subdirectory(extern/whisper.cpp)


add_library(common
        ${WHISPER_EXAMPLES}/common.h
        ${WHISPER_EXAMPLES}/common.cpp
        ${WHISPER_EXAMPLES}/common-sdl.h
        ${WHISPER_EXAMPLES}/common-sdl.cpp

)
target_include_directories(${PROJECT_NAME} PRIVATE ${WHISPER_EXAMPLES})
target_include_directories(${PROJECT_NAME} PRIVATE /usr/include/SDL2)
target_include_directories(common PRIVATE /usr/include/SDL2)
target_include_directories(${PROJECT_NAME} PRIVATE "/home/david/whisper.cpp/include")
target_include_directories(${PROJECT_NAME} PRIVATE "/home/david/whisper.cpp/ggml/include")

target_include_directories(${PROJECT_NAME} PRIVATE "/home/david/whisper.cpp/ggml/include")


target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE whisper)
target_link_libraries(${PROJECT_NAME} PRIVATE common)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2)