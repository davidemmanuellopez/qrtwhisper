cmake_minimum_required(VERSION 3.16)

project(QRTWhisper VERSION 0.1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_AUTOUIC OFF) # No usamos archivos .ui

set (WHISPER_PATH "${CMAKE_SOURCE_DIR}/extern/whisper.cpp")
set(WHISPER_EXAMPLES "${WHISPER_PATH}/examples")

set(WHISPER_MODELS "${WHISPER_PATH}/models")

configure_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/config.h.in"
        "${CMAKE_CURRENT_SOURCE_DIR}/config.h"
)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(${PROJECT_NAME}
        main.cpp
        model.cpp model.h
        controller.cpp controller.h
        TextRender.cpp TextRender.h
        TransparentWindow.cpp
        View.cpp
        MainWidget.cpp
        MainWidget.h
        Tray.cpp
)

add_executable(sdl_mics  sdl_mics.cpp
        Tray.h
)

add_executable(tray_app tray_app.cpp)

set(GGML_CUDA 1)
set(CMAKE_CUDA_ARCHITECTURES "86")
set(WHISPER_SDL2 ON)

#uncomment for hardcode the path to cuda compiler
#set(CMAKE_CUDA_COMPILER /usr/local/cuda-12.9/bin/nvcc)

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
target_include_directories(${PROJECT_NAME} PRIVATE "${WHISPER_PATH}/include")
target_include_directories(${PROJECT_NAME} PRIVATE "${WHISPER_PATH}/ggml/include")

target_link_libraries(${PROJECT_NAME} PRIVATE Qt6::Widgets)
target_link_libraries(${PROJECT_NAME} PRIVATE whisper)
target_link_libraries(${PROJECT_NAME} PRIVATE common)
target_link_libraries(${PROJECT_NAME} PRIVATE SDL2)

target_link_libraries(sdl_mics PRIVATE SDL2)
target_link_libraries(tray_app PRIVATE Qt6::Widgets)

file(COPY "${CMAKE_SOURCE_DIR}/tray_icon.png"
        DESTINATION "${CMAKE_CURRENT_BINARY_DIR}/")

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
# Instalar imagen en rutas estándar (Flatpak o sistema tradicional)
install(FILES tray_icon.png
        DESTINATION bin  # Para iconos del sistema
)

# Habilitar CPack para generar .deb
include(InstallRequiredSystemLibraries)
set(CPACK_PACKAGE_NAME "qrtwhisper")
set(CPACK_PACKAGE_VERSION "1.0")
set(CPACK_PACKAGE_DESCRIPTION "Aplicación con SDL2 y CUDA")
set(CPACK_PACKAGE_CONTACT "tucorreo@example.com")
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "Tu Nombre")
set(CPACK_PACKAGE_VENDOR "TuEmpresa")

# Dependencias del paquete (.deb)
set(CPACK_DEBIAN_PACKAGE_DEPENDS "libsdl2-2.0-0, cuda-runtime-12-9")

# Generador DEB (requiere 'dpkg' instalado)
set(CPACK_GENERATOR "DEB")

include(CPack)