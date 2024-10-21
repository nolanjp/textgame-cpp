cmake_minimum_required(VERSION 3.27)
project(text_game)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(text_game
        area.cpp
        area.h
        character.cpp
        character.h
        game_map.txt
        inventory.cpp
        inventory.h
        item.cpp
        item.h
        main.cpp
        player.cpp
        player.h
        room.cpp
        room.h)
