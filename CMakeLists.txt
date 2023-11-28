cmake_minimum_required (VERSION 3.27)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARTREQUIRED True)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (SnakeGame)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)

file(COPY ${CMAKE_SOURCE_DIR}/resources DESTINATION ${CMAKE_BINARY_DIR})

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)

FetchContent_MakeAvailable(SFML)

add_executable (SnakeGame "src/main.cpp" "src/main.h")

set(SRC 
"src/Field/Field.h"
"src/Field/Field.cpp"
"src/Entities/Entity.h"
"src/Entities/Entity.cpp"
"src/Entities/Apple.h"
"src/Entities/Apple.cpp"
"src/Entities/Snake.h"
"src/Entities/Snake.cpp"
"src/Game.h"
"src/Game.cpp"
"src/States/State.h"
"src/States/States.h"
"src/States/States.cpp"
"src/States/StateMachine.h"
"src/States/StateMachine.cpp"
 "src/Factories/AppleFactory.h"
 "src/Factories/AppleFactory.cpp"
 "src/Random.h"
 "src/Random.cpp")

target_sources(SnakeGame PRIVATE ${SRC})
target_link_libraries(SnakeGame PRIVATE sfml-graphics)
target_compile_features(SnakeGame PRIVATE cxx_std_17)


if(WIN32)
    add_custom_command(
        TARGET SnakeGame
        COMMENT "Copy OpenAL DLL"
        PRE_BUILD COMMAND ${CMAKE_COMMAND} -E copy ${SFML_SOURCE_DIR}/extlibs/bin/$<IF:$<EQUAL:${CMAKE_SIZEOF_VOID_P},8>,x64,x86>/openal32.dll $<TARGET_FILE_DIR:SnakeGame>
        VERBATIM)
endif()

install(TARGETS SnakeGame)