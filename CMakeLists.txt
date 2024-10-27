cmake_minimum_required(VERSION 3.30 FATAL_ERROR)

project(playing_cards_core)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED TRUE)

include_directories(includes)

# Using GTest for unit testing
include(FetchContent)
FetchContent_Declare(
    googletest
    GIT_REPOSITORY https://github.com/google/googletest.git
    GIT_TAG        v1.15.2
)

FetchContent_GetProperties(googletest)
FetchContent_MakeAvailable(googletest)

enable_testing()

if(${CMAKE_SYSTEM_NAME} MATCHES "Darwin")
    message("** Building for Mac OS")
    add_subdirectory(${CMAKE_SOURCE_DIR}/submodules/rapidjson)
    add_subdirectory(${CMAKE_SOURCE_DIR}/submodules/spdlog)

    include_directories(
        /System/Library/Frameworks
        ${CMAKE_SOURCE_DIR}/submodules/rapidjson/include
        ${CMAKE_SOURCE_DIR}/submodules/spdlog/include
    )

    set_target_properties(spdlog PROPERTIES IMPORTED_LOCATION 
        ${CMAKE_CURRENT_BINARY_DIR}/submodules/spdlog/libspdlog.dylib)    

    add_library(ProgBarLibTest STATIC src/aux/progbar.cc)
    add_library(CardsLib STATIC src/cards.cc)

    add_executable(
        cardstest
        unittest/cardstest.cc
    )

    target_link_libraries(
        cardstest
        ProgBarLibTest
        CardsLib
        gtest_main
        spdlog
    )
elseif(${CMAKE_SYSTEM_NAME} MATCHES "Linux")
    message("** Building for Mac OS (TODO)")
else()
    message(FATAL_ERROR "Only Mac and Linux officially supported.")
endif()

include(GoogleTest)
gtest_discover_tests(cardstest)
