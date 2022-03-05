cmake_minimum_required(VERSION 2.6)

project(VitaEngine LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

#uncomment below line for debugging
#add_definitions(-DSTD_SR1_DEBUG)

include_directories(
        shared/include/common
        src
)

file(GLOB ENGINEFILES
        src/engine/*.cpp
        src/engine/*.h)

add_library(VitaEngine ${ENGINEFILES})

file (GLOB RENDFILES
    shared/include/common/rend/*.cpp
    shared/include/common/rend/*.h)

add_library(rend ${RENDFILES})

if (MSVC)
  link_directories(${CMAKE_SOURCE_DIR}/shared/lib/msvc)
  target_include_directories(VitaEngine PUBLIC ${CMAKE_SOURCE_DIR}/shared/include/msvc)
  target_link_libraries(VitaEngine rend SDL2 glew32 opengl32 OpenAL32)
else()
  #uncomment below line if it doesn't build
  #link_directories(${CMAKE_SOURCE_DIR}/shared/lib/gcc)
  target_include_directories(VitaEngine PUBLIC ${CMAKE_SOURCE_DIR}/shared/include/gcc)
  target_link_libraries(VitaEngine rend SDL2 GLEW GL GLU openal)
endif()

add_executable(VitaDemo
        src/game/main.cpp
        src/game/Player.cpp
        src/game/Player.h
)

target_link_libraries(VitaDemo VitaEngine)

if (MSVC)
  add_custom_command(TARGET VitaDemo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/shared/lib/msvc/SDL2.dll"
      "$<TARGET_FILE_DIR:VitaDemo>"
  )
  add_custom_command(TARGET VitaDemo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/shared/lib/msvc/glew32.dll"
      "$<TARGET_FILE_DIR:VitaDemo>"
  )   
  add_custom_command(TARGET VitaDemo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/shared/lib/msvc/OpenAL32.dll"
      "$<TARGET_FILE_DIR:VitaDemo>"
  )
  
else()  
  add_custom_command(TARGET VitaDemo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/shared/lib/gcc/libSDL2.a"
      "$<TARGET_FILE_DIR:VitaDemo>"
  )
  add_custom_command(TARGET VitaDemo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/shared/lib/gcc/libglew32.a"
      "$<TARGET_FILE_DIR:VitaDemo>"
  )   
  add_custom_command(TARGET VitaDemo POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_if_different
      "${CMAKE_SOURCE_DIR}/shared/lib/gcc/libOpenAL32.a"
      "$<TARGET_FILE_DIR:VitaDemo>"
  )
endif()
