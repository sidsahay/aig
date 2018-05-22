cmake_minimum_required(VERSION 3.2)
project(aig)

set(CMAKE_CXX_STANDARD 14)

#aigmain executable
add_executable(aigmain
        aigmain/aigmain/graphics.h
        aigmain/aigmain/graphics.cpp
        aigmain/aigmain/observer.h
        aigmain/aigmain/observer_impl.h
        aigmain/aigmain/geometry.h
        aigmain/aigmain/geometry.cpp
        aigmain/aigmain/physics.h
        aigmain/aigmain/geometry.cpp
        aigmain/aigmain/game.h
        aigmain/aigmain/game_impl.h
        aigmain/aigmain/dummy.h
        aigmain/aigmain/dummy.cpp
        aigmain/aigmain/main.cpp)

find_library(SDL2_LIB SDL2)
if(NOT SDL2_LIB)
    message(WARNING "SDL2 library not found explicitly. Build may still work if the linker can find it.")
    target_link_libraries(aigmain SDL2)
else()
    target_link_libraries(aigmain ${SDL2_LIB})
endif()

target_link_libraries(aigmain dl)