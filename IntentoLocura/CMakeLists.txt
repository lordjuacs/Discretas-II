cmake_minimum_required(VERSION 3.15)
project(IntentoLocura)

set(SFML_STATIC_LIBRARIES TRUE)
set(CMAKE_CXX_STANDARD 17)
find_package(SFML 2.5.1 COMPONENTS system window graphics)
add_executable(IntentoLocura main.cpp Clases.h Algoritmos.h Grafico.h InputOutput.h Tipos.h)
target_link_libraries(IntentoLocura sfml-system sfml-window sfml-graphics -static)